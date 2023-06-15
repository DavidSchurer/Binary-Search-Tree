// ---------------------------- bintree.cpp ----------------------------
// David Schurer
// CSS 343
// Creation Date: 4/12/2023
// Date of Last Modification: 4/20/2023
// ---------------------------------------------------------------------
// Purpose - The bintree.cpp is the implemenation file for the binary search
// tree class that implements all of the public and private methods of the
// binary search tree class. It includes the implemenation for the overloaded
// operator methods, inserting a node into the tree, receiving the height
// of a given node in the tree, etc. Each method is commented to explain its
// function and comments are included within the implementation details of
// each method in the class.
// ---------------------------------------------------------------------
// Notes - The binary search tree class uses operator overloading in the
// implementation of the overloaded =, ==, !=, and << methods. It also uses
// recursion in many methods in regards to traversing the binary search tree and
// utilizes helper methods to help with the implementation of the class methods,
// one key feature is that the inorderHelper method uses an inorder tree traversal
// to traverse the left subtree of the binary search tree, print the node's data, and then
// traverse the right subtree of the binary search tree.
// ---------------------------------------------------------------------
#include "bintree.h"
#include <iostream>
#include <queue>
using namespace std;

// -----------------------------[Default Constructor]-----------------------------------------
// Description: The default constructor for the BinTree class initializies an empty
// binary search tree by setting the root of the tree to nullptr.
// -------------------------------------------------------------------------------------------
BinTree::BinTree()
{
	// Initialize the root to nullptr
	root = nullptr;
}
// -------------------------------------------------------------------------------------------

// ------------------------------[Copy Constructor]-------------------------------------------
// Description: The copy constructor for the BinTree class creates a binary search
// tree which is a copy of the binary search tree otherBinTree that is passed in through
// the method.
// -------------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree &otherBinTree)
{
	// Initialize the root of the new tree to nullptr
	root = nullptr;

	// Call the copy constructor helper method to copy the nodes of otherBinTree
	copyConstructorHelper(root, otherBinTree.root);
}
// -------------------------------------------------------------------------------------------

// ----------------------------[copyConstructorHelper]----------------------------------------
// Description: The copyConstructorHelper method is the helper method for the
// copy constructor that creates the new nodes for the new binary search tree and copies
// the data from the nodes of the other binary search tree into the new binary search tree.
// The new binary search tree that is created is a deep copy of the other binary search tree.
// -------------------------------------------------------------------------------------------
void BinTree::copyConstructorHelper(Node* &newBinTreeNode, Node* otherBinTreeNode) const
{
	// If the other binary tree node is a nullptr, set the new binary tree node to nullptr
	if (otherBinTreeNode == nullptr)
	{
		newBinTreeNode = nullptr;
	}

	if (otherBinTreeNode != nullptr)
	{
		// Create a new node and copy the data from the other binary tree node into the new binary tree node data
		newBinTreeNode = new Node();
		newBinTreeNode->data = new NodeData(*otherBinTreeNode->data);

		// Recursively copy the nodes from the left subtree and right subtree of the other
		// binary tree into the new binary tree
		copyConstructorHelper(newBinTreeNode->left, otherBinTreeNode->left);
		copyConstructorHelper(newBinTreeNode->right, otherBinTreeNode->right);
	}
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[Destructor]----------------------------------------------
// Description: The destructor of the BinTree class frees up all of the memory that was dynamically
// allocated by the binary search tree, it frees up memory by deleting all of the nodes in the
// binary search tree by calling the makeEmpty method.
// -------------------------------------------------------------------------------------------
BinTree::~BinTree()
{
	// Call the makeEmpty method to make the tree empty
	makeEmpty();
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[makeEmpty]-----------------------------------------------
// Description: The makeEmpty method of the BinTree class makes the binary search tree empty
// by removing all of the nodes from the binary search tree and deallocating the memory
// that was used by the nodes in the binary search tree, this method does this by calling
// the emptyBinTreeHelper method, which will use a postorder traversal to delete all of the
// nodes in the binary search tree.
// -------------------------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	// Call the empty binary tree helper method to delete all of the nodes in the tree
	emptyBinTreeHelper(root);
	root = nullptr;
}
// -------------------------------------------------------------------------------------------

// ----------------------------[emptyBinTreeHelper]-------------------------------------------
// Description: The emptyBinTreeHelper method is the helper method for the makeEmpty method that
// empties the binary search tree by recursively deleting all of the nodes in the tree
// and deallocating their memory.
// -------------------------------------------------------------------------------------------
void BinTree::emptyBinTreeHelper(Node* &node) 
{
	// If the node is nullptr, return from the method (tree is empty)
	if (node == nullptr) 
	{
		return;
	}

	// If the node is not nullptr, recursively delete the left and right subtrees of that node
	if (node != nullptr)
	{
		// Recursively delete the nodes from the left and right subtrees
		emptyBinTreeHelper(node->left);
		emptyBinTreeHelper(node->right);

		// Deallocates the node data, then the node itself, then sets the node to nullptr
		delete node->data;
		delete node;
		node = nullptr;
	}
}
// -------------------------------------------------------------------------------------------

// ------------------------------------[isEmpty]----------------------------------------------
// Description: The isEmpty method of the BinTree class returns true if the binary search tree
// is empty or false if the binary search tree is not empty.
// -------------------------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
	// Returns true if the root is equal to nullptr, false otherwise
    return root == nullptr;
}
// -------------------------------------------------------------------------------------------

// -----------------------------------[getHeight]---------------------------------------------
// Description: The getHeight method of the BinTree class returns the height of the given
// nodeData value in the binary search tree by calling the getHeightHelper method.
// -------------------------------------------------------------------------------------------
int BinTree::getHeight(const NodeData& nodeData) const 
{
	// Calls the getHeight helper method to calculate the height of the given nodeData
	// in the binary search tree
   return getHeightHelper(nodeData, root); 
}
// -------------------------------------------------------------------------------------------

// --------------------------------[getHeightHelper]------------------------------------------
// Description: The getHeightHelper method of the BinTree class calculates the height
// of the given nodeData value in the binary search tree by recursively finding the
// height of the node's left and right subtrees and returning the larger height
// between the two subtrees.
// -------------------------------------------------------------------------------------------
int BinTree::getHeightHelper(const NodeData& nodeData, Node* currentNode) const 
{
	// Return 0 if the current node is a nullptr
	 if (currentNode == nullptr)
	 {
		return 0;
	 }
	 
	 // If the current node's data is equal to the nodeData we are looking for, call the 
	 // getHeight recursive helper method to find the height of that nodeData
	 if (*currentNode->data == nodeData)
	 {
		return getHeightRecursiveHelper(currentNode);
	 }
	
	// Calculates the height of the left subtree of the tree rooted at nodeData
	int leftSubTreeHeight = getHeightHelper(nodeData, currentNode->left);

	// Calculates the height of the right subtree of the tree rooted at nodeData
	int rightSubTreeHeight = getHeightHelper(nodeData, currentNode->right);

	// Returns whichever of the two subtrees of the nodeData node have a greater height
	if (leftSubTreeHeight > rightSubTreeHeight)
	{
		return leftSubTreeHeight;
	}
	else
	{
		return rightSubTreeHeight;
	}
}
// -------------------------------------------------------------------------------------------

// ---------------------------[getHeightRecursiveHelper]--------------------------------------
// Description: The getHeightRecursiveHelper method is called by the getHeightHelper
// method in the BinTree class when the target nodeData value is equal to the current node.
// This method uses recursion to find the max height between the two subtrees rooted
// at the current node, and returns the largest height between the two subtrees + 1
// to account for the nodeData node itself.
// -------------------------------------------------------------------------------------------
int BinTree::getHeightRecursiveHelper(Node* currentNode) const
{
	// If the current node is nullptr, 0 is returned as its height
    if (currentNode == nullptr)
    {
        return 0;
    }

	// Recursively calculates the height of currentNode in the binary search tree by
	// comparing the heights of its left subtree and its right subtree and returning the highest
	// height of the two subtrees + 1 to account for the currentNode itself
	if (getHeightRecursiveHelper(currentNode->left) > getHeightRecursiveHelper(currentNode->right))
	{
		return getHeightRecursiveHelper(currentNode->left) + 1;
	}
	else
	{
		return getHeightRecursiveHelper(currentNode->right) + 1;
	}
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[bstreeToArray]-------------------------------------------
// Description: The bstreeToArray method for the BinTree class converts a binary
// search tree into an array. It passes in an array of NodeData objects as its
// parameter and calls the bstreeToArrayRecursiveHelper method to add all of the nodes
// from the binary search tree into the array using an inorder traversal. After all of the
// nodes have been added to the array, the binary search tree is emptied.
// -------------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* nodeDataArray[])
{
	// arrayIndex is used to keep track of the current position in the array as it is built
	int arrayIndex = 0;

	// The bstreeToArray helper method is called to add all of the nodes from the binary search tree to the array
	bstreeToArrayRecursiveHelper(this->root, nodeDataArray, arrayIndex);

	// After all of the nodes from the binary search tree have been added to the array, the binary search tree is emptied
	this->root = nullptr;
}
// -------------------------------------------------------------------------------------------

// -------------------------[bstreeToArrayRecursiveHelper]------------------------------------
// Description: The bstreeToArrayRecursiveHelper is the helper method for the
// bstreeToArray method that traverses the binary search tree recursively using an
// inorder traversal and adding each of the node's data from the binary search tree
// into the array at the given index.
// -------------------------------------------------------------------------------------------
void BinTree::bstreeToArrayRecursiveHelper(Node* currentNode, NodeData* nodeDataArray[], int& arrayIndex)
{
	// If the size of the array is equal to or greater than 100 (full), or the current node
	// is a nullptr, we return
	if (arrayIndex >= 100 || currentNode == nullptr)
	{
		return;
	}

	// If the size of the array is smaller than 100 (not full), we can recursively add
	// the nodes from the binary search tree to the array 
	else if (!(arrayIndex >= 100) || currentNode != nullptr)
	{
		// Helper method recursively calls itself to traverse the left subtree of the binary search tree
		bstreeToArrayRecursiveHelper(currentNode->left, nodeDataArray, arrayIndex);

		// At the given index of the array, the binary search tree's node data is added into the 
		// array, then that node's data of the binary search tree is set to nullptr and we increment the index of the array
		nodeDataArray[arrayIndex] = currentNode->data;
		currentNode->data = nullptr;
		arrayIndex++;

		// Helper method recursively calls itself to traverse the right subtree of the binary search tree
		bstreeToArrayRecursiveHelper(currentNode->right, nodeDataArray, arrayIndex);
		
		// After we have added the node from the binary search tree to the array, delete that node from the binary search tree
		delete currentNode;
	}
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[arrayToBSTree]-------------------------------------------
// Description: The arrayToBSTree method for the BinTree class converts the
// given array of nodeData objects  into a binary search tree. The binary search
// tree is initialized to an empty tree and then the size of the array is determined
// by counting the non-nullptr nodeData objects in the array before calling it's
// recursive helper method to convert the array to a binary search tree.
// -------------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* nodeDataArray[])
{
	// Size of the array is set to 0 and the binary search tree is emptied
	int arraySize = 0;
	makeEmpty();
	
	// We iterate over the nodeDataArray and find the number of entries that are not
	// nullptr to get the size of the array
	for (int arrayIndex = 0; arrayIndex < 100; arrayIndex++)
	{
		if (nodeDataArray[arrayIndex] != nullptr)
		{
			arraySize++;
		}

		else if (nodeDataArray[arrayIndex] == nullptr)
		{
			nodeDataArray[arrayIndex] = nullptr;
		}
	}

	// The arrayToBSTree helper method is called to recursively convert the array to a binary search tree
	arrayToBStreeRecursiveHelper(root, nodeDataArray, 0, arraySize - 1);
}
// -------------------------------------------------------------------------------------------

// --------------------------[arrayToBSTreeRecursiveHelper]-----------------------------------
// Description: The arrayToBSTreeRecursiveHelper method for the BinTree class is the recursive
// helper method for the arrayToBSTree method, this method creates nodeData object
// at the mid index of the array and recursively calls itself for the left and right halves
// of the array until all the items in the array have been added into the binary search tree.
// -------------------------------------------------------------------------------------------
void BinTree::arrayToBStreeRecursiveHelper(Node* currentNode, NodeData* nodeDataArray[], int lowIndex, int highIndex)
{
	// Formula for the midpoint of the array
	int middleIndex = (lowIndex + highIndex) / 2;

	// If the low index is greater than the high index, this indicate that the subtree
	// of the binary search tree is empty, so we set currentNode to nullptr
	if (lowIndex > highIndex)
	{
		currentNode = nullptr;
	}
	else
	{
		// A temporary node data is created and extracts the nodeData object from the midpoint of the array, then this
		// nodeData object is inserted into the binary search tree
		NodeData* temporaryNodeData = nodeDataArray[middleIndex];
		insert(temporaryNodeData);

		// The nodeData object is removed from the array once it is inserted into the binary search tree
		nodeDataArray[middleIndex] = nullptr;

		// The arrayToBSTree helper method recursively calls itself for the left and right sides of the array,
		// which will build the left and right subtress of the binary search tree
		arrayToBStreeRecursiveHelper(currentNode, nodeDataArray, lowIndex, middleIndex - 1);
		arrayToBStreeRecursiveHelper(currentNode, nodeDataArray, middleIndex + 1, highIndex);
	}
}
// -------------------------------------------------------------------------------------------

// ----------------------------------[operator=]----------------------------------------------
// Description: The overloaded assignment operator for the BinTree class assigns one binary 
// search tree object to another binary search tree object by copying all of the nodes from one
// binary search tree to another.
// -------------------------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &otherBinTree)
{
	// If both binary search trees are equal to each other, 
	// return the current binary search tree object
	if (this == &otherBinTree)
	{
		return *this;
	}
	// If the binary search trees are not equal to each other,
	// delete all of the nodes in the current binary search tree
	// and copy the nodes from the other binary search tree
	// into the current one
	else
	{
		makeEmpty();
		copyConstructorHelper(root, otherBinTree.root);
	}

	// Return the current binary search tree object
	return *this;
}
// -------------------------------------------------------------------------------------------

// ----------------------------------[operator==]---------------------------------------------
// Description: The overloaded equality operator for the BinTree class compares two
// binary search trees to see if they are equal or not. If both of the trees are
// empty it will return true, else it will call equalityOperatorHelper to recursively
// compare the nodes of both binary search trees to check if they are equal to each other.
// -------------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &otherBinTree) const
{
	// If both of the binary search trees are not empty, call the helper method
	// to compare the nodes of both binary search trees
   if (root != nullptr && otherBinTree.root != nullptr)
   {
		return equalityOperatorHelper(root, otherBinTree.root);
   }
   
   // If both of the binary search trees are empty, return true as they are both equal
   return true;
}
// -------------------------------------------------------------------------------------------

// ----------------------------[equalityOperatorHelper]---------------------------------------
// Description: The equalityOperatorHelper is the helper method for the overloaded
// equality operator, it recursively compares the left and right subtrees of each node 
// of the two binary search trees to check if they are equal to each other or not, 
// It checks to see if both the tree's structure and the data in their nodes are equal.
// -------------------------------------------------------------------------------------------
bool BinTree::equalityOperatorHelper(Node* currentNode, Node* otherNode) const
{
	// If both nodes in the trees are nullptr, then they are equal
	if (currentNode == nullptr && otherNode == nullptr)
	{
		return true;
	}

	// If the data in the node of the current binary search tree is not equal to the
	// data of the node of the other binary search tree, they are not equal
	if (*currentNode->data != *otherNode->data)
	{
		return false;
	}

	// If the node in one tree is nullptr while the node in the other tree is not nullptr,
	// the trees are not equal
	if ((currentNode == nullptr && otherNode != nullptr) || (currentNode != nullptr && otherNode == nullptr))
	{
		return false;
	}

	// If the data in the nodes of both trees are equal and their left and right subtrees
	// are nullptr, then the trees are equal
	if (*currentNode->data == *otherNode->data)
	{
		if (currentNode->left == nullptr && otherNode->left == nullptr) 
		{
			if (currentNode->right == nullptr && otherNode->right == nullptr)
			{
				return true;
			}
		}
	}

	// If the data in the current tree's node is equal to the other tree's node and their
	// left and right subtrees are not nullptr, the helper method recursively compares
	// their subtrees to see if they are equal
	return (*currentNode->data == *otherNode->data && 
	equalityOperatorHelper(currentNode->left, otherNode->left) && 
	equalityOperatorHelper(currentNode->right, otherNode->right));
}
// -------------------------------------------------------------------------------------------

// ----------------------------------[operator!=]---------------------------------------------
// Description: The overloaded inequality operator for the BinTree class compares two binary
// search trees to see if they are not equal, if both of the trees are empty, return false,
// else call the inequalityOperatorHelper method to recursively compare the nodes in both trees
// to see if they are not equal.
// -------------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &otherBinTree) const
{
   // If both of the binary search trees are not empty, call the helper method
   // to compare the nodes of both trees to see if they are not equal
   if (root != nullptr && otherBinTree.root != nullptr)
   {
		return inequalityOperatorHelper(root, otherBinTree.root);
   }
   
   // If both of the binary search trees are empty, return false as they are equal
   return false;
}
// -------------------------------------------------------------------------------------------

// ----------------------------[inequalityOperatorHelper]-------------------------------------
// Description: The inequalityOperatorHelper is the helper method for the overloaded inequality
// operator for the BinTree class. It compares the data of the nodes in both trees and
// recursively compares each node's left and right subtrees to see if they are not equal
// to each other.
// -------------------------------------------------------------------------------------------
bool BinTree::inequalityOperatorHelper(Node* currentNode, Node* otherNode) const
{
	// If the current binary search tree's node is nullptr and the other binary search tree's
	// node is nullptr, the trees are equal
	if (currentNode == nullptr && otherNode == nullptr)
	{
		return false;
	}

	// If the data in the current tree's node is not equal to the data in the other tree's node,
	// then the trees are not equal
	if (*currentNode->data != *otherNode->data)
	{
		return true;
	}

	// If the node of one of the trees is nullptr while the other one is not, the trees are not equal
	if ((currentNode == nullptr && otherNode != nullptr) || (currentNode != nullptr && otherNode == nullptr))
	{
		return true;
	}

	// If the data of the nodes of the two trees are equal and their left and right subtrees
	// are nullptr, the trees are equal
	if (*currentNode->data == *otherNode->data)
	{
		if (currentNode->left == nullptr && otherNode->left == nullptr) 
		{
			if (currentNode->right == nullptr && otherNode->right == nullptr)
			{
				return false;
			}
		}
	}

	// If the data in the current tree's node is equal to the other tree's node and their
	// left and right subtrees are not nullptr, the helper method recursively compares
	// their subtrees to check if they are not equal
	return (*currentNode->data == *otherNode->data && 
	inequalityOperatorHelper(currentNode->left, otherNode->left) && 
	inequalityOperatorHelper(currentNode->right, otherNode->right));
}
// -------------------------------------------------------------------------------------------

// ----------------------------------[operator<<]---------------------------------------------
// Description: The overloaded output operator for the BinTree class calls the
// recursive helper method inorderHelper to recursively traverse the binary search tree
// using inorder traversal and prints out all of the data of the nodes in the tree.
// -------------------------------------------------------------------------------------------
ostream& operator<<(ostream& out, const BinTree &binTree)
{
	// If the binary search tree is not empty, the inorderHelper method is called
	// to traverse the binary search tree and print out all of its nodes
	if (!binTree.isEmpty())
	{
		binTree.inorderHelper(binTree.root);
	}
	
	// A new line is printed after the tree is printed and the output stream object is returned
	out << endl;
	return out;
}
// -------------------------------------------------------------------------------------------

// ------------------------------------[insert]-----------------------------------------------
// Description: The insert method for the BinTree class inserts a node into the
// binary search tree with a given node data. It traverses the binary search tree
// and compares the data of each node to the new node data that is being passed in.
// -------------------------------------------------------------------------------------------
bool BinTree::insert(NodeData* newNodeData)
{
	// A new node is created with its data set to the passed in node data
	Node* newNode = new Node;
	newNode->data = newNodeData;

	// The new node's left and right pointers are initialized to nullptr
	newNode->left = nullptr;
	newNode->right = nullptr;

	// If the binary search tree is empty, the new node is set as the root
	// of the tree
	if (root == nullptr)
	{
		root = newNode;
		return true;
	}

	// If the tree is not empty, we will traverse the tree by using currentNode
	// and starting from the root of the tree
	Node* currentNode = root;
	Node* parentNode = nullptr;

	while (currentNode != nullptr)
	{
		// If the new node's data is smaller than the current node's data, traverse left
		if (*newNodeData < *currentNode->data)
		{
			parentNode = currentNode;
			currentNode = currentNode->left;
		}

		// If the new node's data is equal to the current node's data, delete the new
		// node and return false as duplicates are not allowed
		else if (*newNodeData == *currentNode->data)
		{
			delete newNode;
			newNode = nullptr;
			return false;
		}

		// If the new node's data is greater than the current node's data, traverse right
		else if (*newNodeData > *currentNode->data)
		{
			parentNode = currentNode;
			currentNode = currentNode->right;
		}
	}
	
	// If the new node's data is smaller than the parent node's data, set the left
	// child of the parent node to the new node
	if (*newNodeData < *parentNode->data)
	{
		parentNode->left = newNode;
	}

	// If the new node's data is equal to the parent node's data, delete the new node
	// and return false as duplicates are not allowed
	else if (*newNodeData == *parentNode->data)
	{
		delete newNode;
		newNode = nullptr;
		return false;
	}

	// If the new node's data is greater than the parent node's data, set the right child
	// of the parent node to the new node
	else if (*newNodeData > *parentNode->data)
	{
		parentNode->right = newNode;
	}

	// Return true as the new node was successfully inserted into the binary search tree
	return true;
}
// -------------------------------------------------------------------------------------------

// -----------------------------------[retrieve]----------------------------------------------
// Description: The retrieve method for the BinTree class searches the binary search tree
// for a given targetNodeData, it searches the tree by comparing the target node's
// data to the current node and returns true if the target node was found or
// false if it was not found.
// -------------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData& targetNodeData, NodeData* &retrievedNodeData)
{
	// Create a new node currentNode that will traverse the tree and look for the target node to retrieve
	Node* currentNode = root;

	while (currentNode != nullptr)
	{
		// If the target node's data is smaller than the current node's data, traverse left
		if (targetNodeData < *currentNode->data)
		{
			currentNode = currentNode->left;
		}

		// If the current node's data is equal to the target node's data, set the retrievedNodeData to
		// that current node's data and return true
		else if (*currentNode->data == targetNodeData)
		{
			retrievedNodeData = currentNode->data;
			return true;
		}

		// If the target node's data is greater than the current node's data, traverse right
		else if (targetNodeData > *currentNode->data)
		{
			currentNode = currentNode->right;
		}
	}

	// Set the retrieved node's data to nullptr and return false if the node was not found in the tree
	retrievedNodeData = nullptr;
	return false;
}
// -------------------------------------------------------------------------------------------

// --------------------------------[displaySideways]------------------------------------------
// Description: The displaySideways method displays the binary search tree
// from its side by calling the sideways method.
// -------------------------------------------------------------------------------------------
void BinTree::displaySideways() const 
{
	// Calls the sideways method to display the binary search tree sideways
	sideways(root, 0);
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[inorderHelper]-------------------------------------------
// Description: The inorderHelper method is a recursive helper method for the
// BinTree class that traverses the binary search tree using an inorder traversal,
// it traverses the left subtree recursively, then prints the node data before traversing
// the right subtree recursively.
// -------------------------------------------------------------------------------------------
void BinTree::inorderHelper(Node* binTreeNode) const
{
	// If the current binary search tree node is not nullptr, an inorder traversal
	// of the tree is performed to print out the data of its nodes
	if (binTreeNode != nullptr)
	{
		// Traverses the left subtree of the binary search tree
		inorderHelper(binTreeNode->left);

		// Prints out the node data
		cout << *binTreeNode->data << " ";

		// Traverses the right subtree of the binary search tree
		inorderHelper(binTreeNode->right);
	}
}
// -------------------------------------------------------------------------------------------

// ------------------------------------[sideways]---------------------------------------------
// Description: The sideways method is the recursive helper method for the
// displaySideways method that traverses the trees right subtree, then it's current node,
// then it's left subtree and prints each node's data in a sideways manner.
// -------------------------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const 
{
	// If the current node is not null
	if (current != NULL) {
		level++;
		// The right subtree is traversed recursively
		sideways(current->right, level);

		// 4 Spaces are outputted for each depth level for readability
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		// The data of the current node is printed out followed by a newline
		cout << *current->data << endl; 

		// The left subtree is traversed recursively
		sideways(current->left, level);
	}
}
// -------------------------------------------------------------------------------------------
