// ----------------------------- bintree.h -----------------------------
// David Schurer
// CSS 343
// Creation Date: 4/12/2023
// Date of Last Modification: 4/20/2023
// ---------------------------------------------------------------------
// Purpose - The bintree.h file is the header file for the BinTree class,
// it contains all of the method declarations for the binary search tree
// class including all of its helper methods and the Node struct which represents
// each Node in the binary search tree.
// ---------------------------------------------------------------------
// Notes - The BinTree class uses many helper methods to help implement the
// various different class methods such as makeEmpty, getHeight, bstreeToArray,
// arrayToBSTree, and the overloaded equality and inequality operators of
// the binary search tree class.
// ---------------------------------------------------------------------
#ifndef BIN_TREE_H
#define BIN_TREE_H
#include "nodedata.h"
#include <iostream>
using namespace std;

class BinTree {

    private:
        // The Node struct defines the structure of the node in the binary search tree,
        // each node has a pointer to a NodeData data, a pointer to a left child,
        // and a pointer to a right child
        struct Node {
            NodeData* data;                            
            Node* left;                                 
            Node* right;                               
        };

        // Pointer to the root node of the binary search tree
        Node* root;                                   

    // Helper methods for inorder traversal, displaySideways, and the copy constructor
    void inorderHelper(Node* binTreeNode) const;
    void sideways(Node* current, int level) const;                  
    void copyConstructorHelper(Node* &newBinTreeNode, Node* otherBinTreeNode) const;

    public:
        // Binary search tree constructor, copy constructor, and destructor
        BinTree();                                     
        BinTree(const BinTree &otherBinTree);          
        ~BinTree();   

        // makeEmpty and its helper method used to delete all of the nodes in the tree                         
        void makeEmpty(); 
        void emptyBinTreeHelper(Node* &node);  

        // isEmpty checks to see if the tree is empty
        bool isEmpty() const;                           

        // Overloaded =, ==, !=, << operators
        BinTree& operator=(const BinTree &otherBinTree);
        bool operator==(const BinTree &otherBinTree) const;   
        bool operator!=(const BinTree &otherBinTree) const;             
        friend ostream& operator<<(ostream& out, const BinTree &binTree);

        // Helper methods for the overloaded == and != operators  
        bool equalityOperatorHelper(Node* currentNode, Node* otherNode) const;   
        bool inequalityOperatorHelper(Node* currentNode, Node* otherNode) const;
      
        // Insert and retrieve methods
        bool insert(NodeData* newNodeData);                        
        bool retrieve(const NodeData &targetNodeData, NodeData* &retrievedNodeData);   

        // Method to display the tree sideways
        void displaySideways() const;                
        
        // Method to get the height of a given node in the tree, has a helper method and a recursive helper method
        int getHeight (const NodeData &nodeData) const;
        int getHeightHelper(const NodeData& nodeData, Node* currentNode) const;
        int getHeightRecursiveHelper(Node* currentNode) const;
    
        // Methods to convert the binary search tree into an array
        // and to convert an array into a binary search tree
        void bstreeToArray(NodeData* nodeDataArray[]);
        void arrayToBSTree(NodeData* nodeDataArray[]);

        // Helper methods for the bstreeToArray and arrayToBSTree methods
        void bstreeToArrayRecursiveHelper(Node* currentNode, NodeData* nodeDataArray[], int& arrayIndex);
        void arrayToBStreeRecursiveHelper(Node* currentNode, NodeData* nodeDataArray[], int lowIndex, int highIndex);
};

#endif
