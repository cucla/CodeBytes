using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace BST
{
    public class Node<T> where T : IComparable
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
        where T : IComparable
    {
        public NodeList() : base() { }
        public NodeList(int initialSize)
        {
            for (var i = 0; i < initialSize; i++)
            {
                base.Items.Add(default(Node<T>));
            }
        }
    }

    public class BinaryTreeNode<T> : Node<T>
        where T : IComparable
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

        public bool Insert(T insertValue)
        {
            if (insertValue.CompareTo(base.Data) < 0)
            {
                if (Left == null)
                    Left = new BinaryTreeNode<T>(insertValue);
                else
                    Left.Insert(insertValue);
                return true;
            }
            else if (insertValue.CompareTo(base.Data) > 0)
            {
                if (Right == null)
                    Right = new BinaryTreeNode<T>(insertValue);
                else
                    Right.Insert(insertValue);
                return true;
            }
            return false;
        }
    }

    public class BinarySearchTree<T>
        where T : IComparable
    {
        private BinaryTreeNode<T> _root;  // leave it private
        private int _count;

        public BinarySearchTree()
        {
            Root = null;
            Count = 0;
        }

        public BinaryTreeNode<T> Root  // just for print function
        {
            get { return _root; }
            set { _root = value; }
        }

        public int Count
        {
            get { return _count; }
            set { _count = value; }
        }

        public void InsertNode(T data)
        {
            if (Root == null)
            {
                Root = new BinaryTreeNode<T>(data);
                Count++;
            }
            else
            {
                if (Root.Insert(data))
                    Count++;
            }
        }

        // TRAVERSAL

        public void PreorderTraversal()
        {
            PreorderHelper(Root);
        }
        private void PreorderHelper(BinaryTreeNode<T> node)
        {
            if (node != null)
            {
                Console.Write($"{node.Data.ToString()} ");
                PreorderHelper(node.Left);
                PreorderHelper(node.Right);
            }
        }

        public void InorderTraversal()
        {
            InorderHelper(Root);
        }
        private void InorderHelper(BinaryTreeNode<T> node)
        {
            if (node != null)
            {
                InorderHelper(node.Left);
                Console.Write($"{node.Data.ToString()} ");
                InorderHelper(node.Right);
            }
        }

        public void PostorderTraversal()
        {
            PostorderHelper(Root);
        }
        private void PostorderHelper(BinaryTreeNode<T> node)
        {
            if (node != null)
            {
                PostorderHelper(node.Left);
                PostorderHelper(node.Right);
                Console.Write($"{node.Data.ToString()} ");
            }
        }

        // SEARCH

        public BinaryTreeNode<T> FindSmallestBST()
        {
            return FindSmallestHelper(Root);
        }
        private BinaryTreeNode<T> FindSmallestHelper(BinaryTreeNode<T> node)
        {
            if (node != null)
            {
                if (node.Left == null)
                    return node;
                return FindSmallestHelper(node.Left);
            }
            return null;
        }

        public BinaryTreeNode<T> FindLargestBST()
        {
            return FindLargestHelper(Root);
        }
        private BinaryTreeNode<T> FindLargestHelper(BinaryTreeNode<T> node)
        {
            if (node != null)
            {
                if (node.Right == null)
                    return node;
                return FindLargestHelper(node.Right);
            }
            return null;
        }

        public BinaryTreeNode<T> FindNodeBST(T searchVal)
        {
            return FindNodeHelper(Root, searchVal);
        }
        private BinaryTreeNode<T> FindNodeHelper(BinaryTreeNode<T> node, T searchVal)
        {
            if (node != null)
            {
                if (searchVal.CompareTo(node.Data) == 0)
                    return node;
                else if (searchVal.CompareTo(node.Data) < 0)
                    return FindNodeHelper(node.Left, searchVal);
                else 
                    return FindNodeHelper(node.Right, searchVal);
            }
            return null;
        }

        public bool DeleteNode(BinaryTreeNode<T> node, T searchVal, BinaryTreeNode<T> parentNode = null)
        {
            if (node == null)
                return false;
            else
            {
                var result = searchVal.CompareTo(node.Data);
                BinaryTreeNode<T> currentNode = node;

                while (result != 0)
                {
                    if (result < 0)
                    {
                        parentNode = currentNode;
                        currentNode = currentNode.Left;
                    }
                    if (result > 0)
                    {
                        parentNode = currentNode;
                        currentNode = currentNode.Right;
                    }
                    if (currentNode == null)
                        return false;
                    else
                        result = searchVal.CompareTo(currentNode.Data);
                }

                if (currentNode.Left == null)
                {
                    if (parentNode.Left == currentNode)
                        parentNode.Left = currentNode.Right;
                    else
                        parentNode.Right = currentNode.Right;
                    Count--;
                    return true;
                }
                else if (currentNode.Right == null)
                {
                    if (parentNode.Left == currentNode)
                        parentNode.Left = currentNode.Left;
                    else
                        parentNode.Right = currentNode.Left;
                    Count--;
                    return true;
                }
                else
                {
                    var largestLeft = FindLargestHelper(currentNode.Left);
                    currentNode.Data = largestLeft.Data;
                    DeleteNode(largestLeft, largestLeft.Data, currentNode);
                }
            }
            return true;
        }

        public void Clear()
        {
            Root = null;
            Count = 0;
        }
    }
}
