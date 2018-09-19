#include "BinaryTree.h"
#include "Utils.h"

bool Node::nInsert(int i, void* data)
{
	return nInsertNode(new Node(this, i, data));
}

Node* Node::nSearch(int i)
{
	if (mItem == i) { return this; }
	else if (i < mItem && mLeft != NULL ) { return mLeft->nSearch(i);  }
	else if (mItem < i && mRight != NULL) { return mRight->nSearch(i); }
	else //Item Could not be found
	{
		return NULL;
	}
}

int Node::nSize(int i)
{
	i++;
	if (mLeft  != NULL)  { i = mLeft->nSize(i);  }
	if (mRight != NULL)  { i = mRight->nSize(i); }
	return i;
}

Node** Node::nDump(int* index, Node** contents)
{
	if (contents == 0)
	{
		contents = new Node*[nSize()];
	}
	contents[*index] = this;
	*index = (*index + 1);


	if (mLeft != NULL ) { mLeft->nDump(index, contents);  }
	if (mRight != NULL) { mRight->nDump(index, contents); }

	return contents;
}

bool Node::nInsertNode(Node* n)
{

	if (n->mItem < mItem)
	{
		if (mLeft == NULL)
		{
			mLeft = n; 
			n->mParent = this;
			return true; 
		}
		else { return mLeft->nInsertNode(n); }
	} 

	else if (mItem < n->mItem)
	{
		if (mRight == NULL) 
		{ 
			mRight = n; 			
		n->mParent = this;
		return true; 
		}
		else { return mRight->nInsertNode(n); }
	}
	else// i==mItem this should never happen
	{
		//error
		return false;
	}
}

bool Node::nInsertNodeAtRoot(Node* n)
{
	if (mParent != NULL)
	{
		return mParent->nInsertNodeAtRoot(n);
	}
	else
	{
		bool r = nInsertNode(n);
		return r;
	}
}

void Node::nDelete()
{
	if (mParent == NULL)
	{
		assert(false);
	}
	else if (mParent->mLeft  == this) { mParent->mLeft = NULL;  }
	else if (mParent->mRight == this) { mParent->mRight = NULL; }
	else 
	{
		assert(false);
		return; //node listed as parent is does not have this node as a child. Tree broken.
	}
		 if (mLeft != NULL) 
		 {
			 nInsertNodeAtRoot(mLeft); 
			 //mParent->nInsertNode(mLeft);
			 mLeft->nDelete();
		 }
		 if (mRight != NULL)
		 {
			 nInsertNodeAtRoot(mRight); 	
			 //mParent->nInsertNode(mRight);
			 mRight->nDelete();
		 }
	//delete this;
}

void Node::rotate_left()
{
	Node* parent_i = mParent;
	Node* left_i  = mLeft;
	Node* right_i = mRight;
	
		 if (mParent->mLeft == this) { mParent->AttachLeft(left_i); }
	else if (mParent->mRight == this) { mParent->AttachRight(left_i); }

	Node* orphan = left_i->mLeft;
	left_i->AttachLeft(this);

	mRight->AttachRight(orphan);
}

void Node::rotate_right()
{
	Node* parent_i = mParent;
	Node* left_i = mLeft;
	Node* right_i = mRight;

		 if (mParent->mLeft == this) { mParent->AttachLeft(right_i); }
	else if (mParent->mRight == this) { mParent->AttachRight(right_i); }

	Node* orphan = right_i->mRight;
	left_i->AttachRight(this);

	mRight->AttachLeft(orphan);
}
