#include <cmath>
using namespace std;
/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++()
{
	if (ptr_->right != NULL) { // find the leftmost child of the right node
		ptr_ = ptr_->right;
		while (ptr_->left != NULL) { ptr_ = ptr_->left; }
	}
	else { // go upwards along right branches...  stop after the first left
		while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
		ptr_ = ptr_->parent;
	}
	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const
{
	if (size_ == 0)
	{
		return rope_iterator(root);
	}
	Node* currN = root;
	//Loop until reached as far left (would be the starting point in any case)
	while (currN->left != nullptr)
	{
		currN = currN->left;
	}
	return rope_iterator(currN);      
}

//DEFAULT CONSTRUCTOR
Rope::Rope()
{
	root = NULL;
	size_ = 0;

}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p)
{
	root = p;
	int size = 0;
	//Get the size of the rope
	getSize(p,size);
	size_ = size;
}

Rope::~Rope()
{
	//Call helper function to destroy rope given root
	destroy_rope(root);
	root = NULL;
}

	
Rope::Rope(const Rope& r)
{
	//Create a copy of the rope
	root = this->copy_rope(r.root);
	//Ensure all pointers are set
	fillInParents(root);
	size_ = r.size_;
}

Rope& Rope::operator= (const Rope& r)
{
		//Destroy the current tree and copy over passed in tree
		this->destroy_rope(root);
		root = this->copy_rope(r.root);
		size_ = r.size_;
		return *this;
}

//Helper method that copies a rope given the root of another rope (recursive)
Node* Rope::copy_rope(Node* old_root)
{
	if (old_root == NULL) return NULL;
	//Set all pointer values
	Node* p = new Node();
	p->weight = old_root->weight;
	p->value = old_root->value;
	p->left = copy_rope(old_root->left);
	p->right = copy_rope(old_root->right);

	//return root of new tree
	return p;
}

//Helper method to ensure all nodes have a parent node (except root)
void Rope::fillInParents(Node* &p)
{
	if (p == NULL)
	{
		return;
	}
	if (!is_leaf(p))
	{
		if (p->left != NULL)
		{
			p->left->parent = p;
		}
		if (p->right != NULL)
		{
			p->right->parent = p;
		}
	}
	else
	{
		return;	
	}
	fillInParents(p->left);
	fillInParents(p->right);
}

//Helper method to destroy rope given the root
void Rope::destroy_rope(Node* p)
{
	if (p == NULL) return;

	/* first delete both subtrees */
	destroy_rope(p->left);
	destroy_rope(p->right);

	delete p;
}

//Helper method that returns a node pointer to the node that contains the wanted index
Node* Rope::nodeofIndex(int& incount) const
{
	Node* currNode = root;
	//Ensure not out of bounds
	if (incount >= size_)
	{
		currNode = NULL;
		return currNode;
	}
	while (!is_leaf(currNode))
	{
		//Filter through tree by subtracting weights
		if (currNode->weight > incount)
		{

			currNode = currNode->left;
		}
		else
		{
			//if move right subtract the weight of node
			incount -= (currNode->weight);
			currNode = currNode->right;
		}
	}
	return currNode;
}
//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const
{
	int incount = i;
	//Aquire node
	Node* currNode = nodeofIndex(incount);
	if (currNode == NULL)
	{
		return false;
	}
	c = currNode->value[incount];
	return true;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	size_ = size_ + r.size_;

	//Create new root node and move around pointers from both sides
	Node* newroot = new Node();
	newroot->left = root;
	newroot->right = r.root;
	root->parent = newroot;
	r.root->parent = newroot;
	root = newroot;
	if (!is_leaf(root))
	{
		int count = 0;
		//set new weight of root
		nodesWeight(root->left, count);
		root->weight = count;
	}
}
//returns what the weight of any given node should be  (recursive)
void Rope::nodesWeight(Node* p, int& count)
{
	if (is_leaf(p))
	{
		count += p->weight;
		return;
	}
	nodesWeight(p->left,count);
	nodesWeight(p->right,count);
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const
{
	s.clear();
	//Attain the length of what the final string will be
	int length = abs((j - i)) + 1;
	int inindex = i;

	//If both i and j are the same, don't need to iterate
	/*
	if (i == j)
	{
		char c;
		//Get index using method
		if (index(i, c) == true)
		{
			s += c;
			return true;
		}
		else
		{
			return false;
		}
	}
	*/
	//attain node of index
	Node* currNode = nodeofIndex(inindex);

	//Iterate through the tree as many times as length of string
	for (int k= 0; k < length; k++)
	{
		//If reached the end of a lead node
		if (currNode->weight - 1 == inindex && k != length-1)
		{
			s += currNode->value[inindex];
			int count = i + k + 1;
			
			//Update the current node to the next lead node
			currNode = nodeofIndex(count);
			if (currNode == NULL)
			{
				return false;
			}
			inindex = 0;
		}
		else
		{
			s += currNode->value[inindex];
			inindex++;
		}
	}
	return true;
}
//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	int incount = i;

	//attain current node
	Node* currNode = nodeofIndex(incount);

	//Statements to split apart leaf node into two leaf nodes if index is in the middle
	if (incount != 0)
	{
		currNode->left = new Node();
		currNode->right = new Node();
		string nodevalue = currNode->value;
		currNode->left->value = nodevalue.substr(0, incount);
		currNode->right->value = nodevalue.substr(incount, nodevalue.size() - incount);
		currNode->left->parent = currNode;
		currNode->right->parent = currNode;
		currNode->left->weight = currNode->left->value.size();
		currNode->right->weight = currNode->right->value.size();
		currNode->value = "";
		currNode->weight = currNode->left->weight;
		currNode = currNode->right;
	}
	
	//Keep track of the parent node
	Node* currParent = currNode->parent;

	//Create new rope with one last connection to old rope
	rhs.concatrightsubtree(currNode,currNode->weight);
	
	//Split apart final connection between the two ropes
	if (currParent->right == currNode)
	{
		currParent->right = NULL;
	}
	else if (currParent->left == currNode)
	{
		currParent->left = NULL;
	}
	//Resize
	size_ -= rhs.size_;
	return *this;
}

//Helper method to concat a root node with a pre-existing rope
void Rope::concat_not_copy(Node*& p)
{
	//Create new root and move pointers around
	Node* newroot = new Node();
	newroot->weight = size_;
	newroot->left = root;
	newroot->right = p;
	root = newroot;
	root->right->parent = root;
	root->left->parent = root;
	//Update size of rope
	int size = 0;
	getSize(p,size);
	size_ += size;
}
//Helper method that gives the size of a subtree given the subtrees root node (reccursive)
void Rope::getSize(Node* p, int& size) // p is root
{
	if (p == NULL)
	{
		return;
	}
	if (is_leaf(p))
	{
		size += p->weight;
	}
	getSize(p->right,size);
	getSize(p->left, size);
}
//returns the right subtree of the split subtree
void Rope::concatrightsubtree(Node* curr, int ogweight)
{
		while (curr->parent != NULL)
		{
			if (size_ != 0)
			{
				//Check if the current node is to the right of left of parent
				if (curr == curr->parent->right)
				{
					curr = curr->parent;
				}
				//If equaled to parent on the left
				else if (curr == curr->parent->left)
				{
					//Subtract the weight from node
					curr->parent->weight -= ogweight;
					//Ensure right side exists
					if (curr->parent->right != NULL)
					{
						//Seperate right subtree
						Node* rightside = curr->parent->right;
						curr->parent->right = NULL;
						rightside->parent = NULL;
						int size = 0;
						getSize(rightside, size);
						ogweight += size;

						//Concat right subtree with rhs rope
						concat_not_copy(rightside);
					}
					curr = curr->parent;
				}
			}
			else
			{
				//Simply make the rope equal the singal node
				root = curr;
				size_ = ogweight;
			}
			
		}
}
