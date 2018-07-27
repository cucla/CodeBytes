using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace LyndaExamples
{
    public class Demo
    {
        public static void Show(object input)
        {
            if (!(input is string))
            {
                Console.Write("[");
                var list = input as List<object>;
                foreach (var item in list)
                {
                    Show(item);
                    if (item != list.Last())
                        Console.Write(", ");
                }
                Console.Write("]");
            }
            else
                Console.Write(input);
        }


        static void Main(string[] args)
        {
            string s1 = "great";
            StrBinaryTree strBtree = new StrBinaryTree(s1);
            strBtree.FormTree(strBtree.Root);

            BTreePrinter.Print(strBtree.Root);
            Console.WriteLine();
            Console.WriteLine($"Number of elements is: {strBtree.Count}\n");

            Console.WriteLine("GetNestedListFromTree:");
            List<Object> list = strBtree.GetNestedListFromTree(strBtree.Root);
            Show(list);
            Console.WriteLine();

            if (strBtree.BreadthFirst(strBtree.Root, "great"))
                Console.WriteLine("Found \"great\"!");
            if (strBtree.BreadthFirst(strBtree.Root, "eet"))
                Console.WriteLine("Found \"eet\"!");
            if (strBtree.BreadthFirst(strBtree.Root, "t"))
                Console.WriteLine("Found \"t\"!");




            //var scramblList = new List<string>();
            //strBtree.GetAllScrambled(strBtree.Root, ref scramblList);
            //foreach (var el in scramblList)
            //    Console.Write($" -> {el}");





            //Solution mySolution = new Solution();
            //Console.WriteLine(mySolution.IsScramble("s1", "s2"));


            Console.Read();
        }
     }


    //public class Solution
    //{
    //    public bool IsScramble(string s1, string s2)
    //    {
    //        return true;
    //    }
    //}


    public class Node<T>
    {
        private T _data;
        private NodeList<T> _neighbors = null;

        public Node() { }
        public Node(T data) : this(data, null) { }
        public Node(T data, NodeList<T> neighbors)
        {
            _data = data;
            _neighbors = neighbors;  // can assign one collection to another!
        }

        public T Data
        {
            get { return _data; }
            set { _data = value; }
        }

        public NodeList<T> Neighbors
        {
            get { return _neighbors; }
            set { _neighbors = value; }
        }

    }

    public class NodeList<T> : Collection<Node<T>>
    {
        public NodeList() : base() { }
        public NodeList(int initialSize)
        {
            for (var i = 0; i < initialSize; i++)
                base.Items.Add(default(Node<T>));
        }

        public Node<T> FindByValue(T value)
        {
            foreach (Node<T> node in Items)
            {
                if (node.Data.Equals(value))
                    return node;
            }
            return null;
        }
    }

    public class BinaryTreeNode<T> : Node<T>
    {
        public BinaryTreeNode() : base() { }
        public BinaryTreeNode(T data) : base(data, null) { }
        public BinaryTreeNode(T data, BinaryTreeNode<T> left, BinaryTreeNode<T> right)
        {
            base.Data = data;
            NodeList<T> children = new NodeList<T>(2);
            children[0] = left;
            children[1] = right;
            base.Neighbors = children;
        }

        public BinaryTreeNode<T> Left
        {
            get
            {
                if (base.Neighbors == null)
                    return null;
                else
                    return (BinaryTreeNode<T>)base.Neighbors[0];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);

                base.Neighbors[0] = value;
            }
        }

        public BinaryTreeNode<T> Right
        {
            get
            {
                if (base.Neighbors == null)
                    return null;
                return (BinaryTreeNode<T>)base.Neighbors[1];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);
                base.Neighbors[1] = value;
            }
        }
    }

    public class BinaryTree<T>
    {
        private BinaryTreeNode<T> _root;
        private int _count;

        public BinaryTree()
        {
            _root = null;
            _count = 0;
        }

        public BinaryTreeNode<T> Root
        {
            get { return _root; }
            set { _root = value; }
        }

        public int Count
        {
            get { return _count; }
            set { _count = value; }
        }

        public void Clear()
        {
            _root = null;
            _count = 0;
        }

    }

    public class StrBinaryTree : BinaryTree<string>
    {
        public StrBinaryTree(string data)
        {
            if (data.Length == 0)
            {
                base.Root = null;
                base.Count = 0;
            }
            else
            {
                base.Root = new BinaryTreeNode<string>();
                base.Root.Data = data;
                base.Count = 1;
            }
        }

        public void FormTree(BinaryTreeNode<string> node)
        {
            var subLength = node.Data.Length / 2;
            if (subLength == 0)
                return;
            
            node.Left = new BinaryTreeNode<string>(node.Data.Substring(0, subLength));
            node.Right = new BinaryTreeNode<string>(node.Data.Substring(subLength));
            base.Count += 2;

            FormTree(node.Left);
            FormTree(node.Right);
        }

        private bool IsLeaf(BinaryTreeNode<string> node)
        {
            return node.Left == null || node.Right == null;
        }

        public List<Object> GetNestedListFromTree(BinaryTreeNode<string> node, List<Object> list = null)
        {
            List<Object> innerList;

            if (IsLeaf(node))
                return list;
            else
            {
                if (list == null)
                {
                    list = new List<Object> { node.Data };
                    innerList = new List<Object>();
                    list.Add(innerList);
                }
                else
                {
                    innerList = new List<Object>();
                    list.Add(innerList);
                }

                foreach (var side in new[] { node.Left, node.Right })
                {
                    innerList.Add(side.Data);
                    GetNestedListFromTree(side, innerList);
                }

                return list;
            }
        }

        public bool PreorderTraversal(BinaryTreeNode<string> node, string searchStr)
        {
            bool found = false;

            if (node != null)
            {
                //Console.WriteLine(node.Data);
                found = node.Data.Equals(searchStr) ? true : false;
                if (!found)
                {
                    found = (PreorderTraversal(node.Left, searchStr) 
                        || PreorderTraversal(node.Right, searchStr));
                }
            }
            return found;
        }

        public bool InorderTraversal(BinaryTreeNode<string> node, string searchStr)
        {
            bool found = false;

            if (node != null)
            {
                found = InorderTraversal(node.Left, searchStr);
                //Console.WriteLine(node.Data);
                found = node.Data.Equals(searchStr) ? true : false;
                if (!found)
                {
                    found = InorderTraversal(node.Right, searchStr);
                }
            }
            return found;
        }

        public bool PostorderTraversal(BinaryTreeNode<string> node, string searchStr)
        {
            bool found = false;
            if (node != null)
            {
                found = PostorderTraversal(node.Left, searchStr);
                if (!found)
                    found = PostorderTraversal(node.Right, searchStr);
                //Console.WriteLine(node.Data);
                if (!found)
                    found = node.Data.Equals(searchStr) ? true : false;
            }
            return found;
        }

        public bool BreadthFirst(BinaryTreeNode<string> node, string searchStr)
        {
            bool found = false;

            Queue myQ = new Queue();
            BinaryTreeNode<string> curNode = new BinaryTreeNode<string>();
            curNode = node;

            while (curNode != null)
            {
                //Console.WriteLine(curNode.Data);
                found = curNode.Data.Equals(searchStr) ? true : false;
                if (!found)
                {
                    foreach (var side in new[] { curNode.Left, curNode.Right })
                    {
                        if (side != null) myQ.Enqueue(side);
                    }
                }
                if (myQ.Count > 0)
                {
                    curNode = (BinaryTreeNode<string>)myQ.Dequeue();
                }
                else
                    curNode = null;
            }
            return found;
        }

        public bool SwapChild(BinaryTreeNode<string> node)
        {
            if (!IsLeaf(node))
            {
                var temp = new BinaryTreeNode<string>();
                temp = node.Left;
                node.Left = node.Right;
                node.Right = temp;
                return true;
            }
            return false;
        }

        public string GetScrambled(BinaryTreeNode<string> node)
        {
            if (node == null) return "";
            else if (IsLeaf(node))
            {
                return node.Data;
            }
            return GetScrambled(node.Left) + GetScrambled(node.Right);
        }

        public void GetAllScrambled(BinaryTreeNode<string> node, ref List<string> lst)
        {
            //if (node.Left == null && node.Right == null)
            //    return;

            //try
            //{
            //    BTreePrinter.Print(node);
            //    lst.Add(GetScrambled(node));
            //    var copyBtree = new StrBinaryTree(node.Data);
            //    FormTree(copyBtree.Root);

            //    if (SwapChild(node))
            //    {
            //        BTreePrinter.Print(node);
            //        lst.Add(GetScrambled(node));
            //    }
            //    GetAllScrambled(node, ref lst);
            //}
            //catch (NullReferenceException ex) { }


            if (node.Data.Length == 1)
                return;

            BTreePrinter.Print(node);
            lst.Add(GetScrambled(node)); 
            var copyBtree = new StrBinaryTree(node.Data);  // second tree - original
            FormTree(copyBtree.Root);

            SwapChild(node);
            BTreePrinter.Print(node);
            lst.Add(GetScrambled(node));  


            SwapChild(copyBtree.Root.Left);
            BTreePrinter.Print(copyBtree.Root);
            lst.Add(GetScrambled(copyBtree.Root));

            SwapChild(copyBtree.Root.Left); // return back
            SwapChild(copyBtree.Root.Right);
            BTreePrinter.Print(copyBtree.Root);
            lst.Add(GetScrambled(copyBtree.Root));
        }

    }

    //------------------------PRINTER------------------------
    public static class BTreePrinter
    {
        class NodeInfo
        {
            public BinaryTreeNode<string> Node;
            public string Text;
            public int StartPos;
            public int Size { get { return Text.Length; } }
            public int EndPos { get { return StartPos + Size; } set { StartPos = value - Size; } }
            public NodeInfo Parent, Left, Right;
        }

        public static void Print(this BinaryTreeNode<string> root, int topMargin = 2, int leftMargin = 2)
        {
            if (root == null) return;
            int rootTop = Console.CursorTop + topMargin;
            var last = new List<NodeInfo>();
            var next = root;
            for (int level = 0; next != null; level++)
            {
                var item = new NodeInfo { Node = next, Text = next.Data };
                if (level < last.Count)
                {
                    item.StartPos = last[level].EndPos + 1;
                    last[level] = item;
                }
                else
                {
                    item.StartPos = leftMargin;
                    last.Add(item);
                }
                if (level > 0)
                {
                    item.Parent = last[level - 1];
                    if (next == item.Parent.Node.Left)
                    {
                        item.Parent.Left = item;
                        item.EndPos = Math.Max(item.EndPos, item.Parent.StartPos);
                    }
                    else
                    {
                        item.Parent.Right = item;
                        item.StartPos = Math.Max(item.StartPos, item.Parent.EndPos);
                    }
                }
                next = next.Left ?? next.Right;
                for (; next == null; item = item.Parent)
                {
                    Print(item, rootTop + 2 * level);
                    if (--level < 0) break;
                    if (item == item.Parent.Left)
                    {
                        item.Parent.StartPos = item.EndPos;
                        next = item.Parent.Node.Right;
                    }
                    else
                    {
                        if (item.Parent.Left == null)
                            item.Parent.EndPos = item.StartPos;
                        else
                            item.Parent.StartPos += (item.StartPos - item.Parent.EndPos) / 2;
                    }
                }
            }
            Console.SetCursorPosition(0, rootTop + 2 * last.Count - 1);
        }

        private static void Print(NodeInfo item, int top)
        {
            SwapColors();
            Print(item.Text, top, item.StartPos);
            SwapColors();
            if (item.Left != null)
                PrintLink(top + 1, "┌", "┘", item.Left.StartPos + item.Left.Size / 2, item.StartPos);
            if (item.Right != null)
                PrintLink(top + 1, "└", "┐", item.EndPos - 1, item.Right.StartPos + item.Right.Size / 2);
        }

        private static void PrintLink(int top, string start, string end, int startPos, int endPos)
        {
            Print(start, top, startPos);
            Print("─", top, startPos + 1, endPos);
            Print(end, top, endPos);
        }

        private static void Print(string s, int top, int left, int right = -1)
        {
            Console.SetCursorPosition(left, top);
            if (right < 0) right = left + s.Length;
            while (Console.CursorLeft < right) Console.Write(s);
        }

        private static void SwapColors()
        {
            var color = Console.ForegroundColor;
            Console.ForegroundColor = Console.BackgroundColor;
            Console.BackgroundColor = color;
        }
    }
    //------------------------PRINTER------------------------

}
