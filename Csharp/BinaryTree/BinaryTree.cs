using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;


namespace CSharpApp2
{
    public class Node<T>
    {
        private T _data;
        private NodeList<T> _neighbors = null;

        public Node() { }
        public Node(T data) : this(data, null) { }
        public Node(T data, NodeList<T> neighbors)
        {
            Data = data;
            Neighbors = neighbors;
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
            for(var i = 0; i < initialSize; i++)
            {
                base.Items.Add(default(Node<T>));
            }
        }

        public Node<T> FindByValue(T value)
        {
            foreach(Node<T> node in base.Items)
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
                else
                    return (BinaryTreeNode<T>)base.Neighbors[1];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);

                base.Neighbors[1] = value;
            }
        }

        public bool IsLeaf()
        {
            if (base.Neighbors == null)
                return true;
            return base.Neighbors.Count == 0;
        }
    }

    public class BinaryTree<T>
    {
        private BinaryTreeNode<T> _root;
        private int _count;

        public BinaryTree()
        {
            Root = null;
            Count = 0;
        }
        public BinaryTree(BinaryTreeNode<T> root)
        {
            Root = root;
            Count = 1;
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
            Root = null;
            Count = 0;
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

        public List<object> GetNestedListFromTree(BinaryTreeNode<string> node, List<object> list = null)
        {
            List<object> innerList;

            if (node.IsLeaf())
                return list;
            else
            {
                if (list == null)
                {
                    list = new List<Object> { node.Data };
                    innerList = new List<object>();
                    list.Add(innerList);
                }
                else
                {
                    innerList = new List<object>();
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

        public void PreorderTraversal(BinaryTreeNode<string> node)
        {
            if (node != null)
            {
                string s = node.IsLeaf() ? "is a leaf" : "is not a leaf";
                Console.WriteLine($"{node.Data}\t{s}");

                PreorderTraversal(node.Left);
                PreorderTraversal(node.Right);
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
                    found = InorderTraversal(node.Right, searchStr);
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
                if (!found)
                {
                    //Console.WriteLine(node.Data);
                    found = node.Data.Equals(searchStr) ? true : false;
                }
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
                        if (side != null) myQ.Enqueue(side);
                }
                if (myQ.Count > 0)
                    curNode = (BinaryTreeNode<string>)myQ.Dequeue();
                else
                    curNode = null;
            }
            return found;
        }
    }
}
