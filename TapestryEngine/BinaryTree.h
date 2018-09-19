#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define NULL 0


class Node
{
public:

	Node() : mParent(NULL), mLeft(NULL), mRight(NULL), mColor(RED)
	{}

	Node(Node* parent, int item, void* data) : mItem(item), mData(data), mParent(parent), mLeft(NULL), mRight(NULL), mColor(RED)
	{}

	Node(int item, void* data) : mItem(item), mData(data), mParent(NULL), mLeft(NULL), mRight(NULL), mColor(BLACK) //Used to create debugging root node w/test data
	{}

//	~Node()
//	{
//		mParent = NULL;
//		mRight = NULL;
//		mLeft = NULL;
//		mData = NULL;
//	}

	bool nInsert(int i, void* data);
	
	Node* nSearch(int i);

	int nSize(int i = 0);

	Node** nDump(int* index, Node** contents = 0); //Should always be called with no arguments, arguements only used for recursion.

	bool nInsertNode(Node* n);

	bool nInsertNodeAtRoot(Node* n);

	void nDelete();

	void rotate_left();
	void rotate_right();

	int GetItem()
	{
		return mItem;
	}

	void* GetData()
	{
		if (mData != NULL)
		{
			return mData;
		}
		else
		{
			return NULL;
		}
	}

	void AttachLeft(Node* n)
	{
		n->mParent = this;
		mLeft = n;
	}

	void AttachRight(Node* n)
	{
		n->mParent = this;
		mRight = n;
	}

	void SwapColor()
	{
		if (mColor == RED) { mColor = BLACK; }
		else               { mColor = RED; }
	}

	Node* mParent;
	Node* mLeft;
	Node* mRight;

protected:

	enum { RED, BLACK } mColor;

	int mItem;

	void* mData;
};


class BinaryTree
{
public:

	BinaryTree() : mRoot(NULL)
	{
	}

	BinaryTree(Node* Root) : mRoot(Root)
	{
	}

	bool Insert(int i, void* data)
	{
		if (mRoot != NULL)
		{
			return mRoot->nInsert(i, data);
		}
		else //mRoot == NULL -> Tree is empty
		{
			mRoot = new Node(i, data);
			return true;
		}
	}

	bool InsertNode(Node* node)
	{	
		if (mRoot != NULL)
		{
			return mRoot->nInsertNode(node);
		}
		else //mRoot == NULL -> Tree is empty
		{
			node->mParent = NULL;
			mRoot = node;
			return true;
		}
	}

	Node* Search(int i)
	{
		if (mRoot != NULL)
		{
			return mRoot->nSearch(i);
		}
		return NULL;
	}

	int Size(int i = 0)
	{
		if (mRoot != NULL)
		{
			return mRoot->nSize(i);
		}
		return -1;
	}

	Node** Dump(Node** contents = 0)
	{
		if (mRoot != NULL)
		{
			int index = 0;
			return mRoot->nDump(&index, contents);
		}
		return NULL;
	}

	void DeleteNode(int node_item)
	{
		Node* target = Search(node_item);
		if (target == mRoot) { mRoot = NULL; }
		else if (target->mParent->mLeft == target) { target->mParent->mLeft = NULL; }
		else if (target->mParent->mRight == target) { target->mParent->mRight = NULL; }
		else
		{
			//assert(false);
			return; //node listed as parent is does not have this node as a child. Tree broken.
		}
		if (target->mLeft != NULL)
		{
			InsertNode(target->mLeft);
			//target->mLeft->nDelete(); //this stuff is all broken. fix it tommorrow
		}
		if (target->mRight != NULL)
		{
			InsertNode(target->mRight);
			//target->mRight->nDelete();
		}
		delete target; 
	}


	void Delete()
	{
		mRoot->nDelete();
	}


protected:

	Node* mRoot;
};
#endif