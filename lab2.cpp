// ----------------------------- lab2.cpp ------------------------------
// David Schurer
// CSS 343
// Creation Date: 4/12/2023
// Date of Last Modification: 4/20/2023
// ---------------------------------------------------------------------
// Purpose - The lab2.cpp file is the driver file that is used to test
// the methods of the binary search tree class BinTree and the node data
// class NodeData. The driver file reads in data from the text file data2.txt,
// this is the text file that contains various strings that will be used to
// build each binary search tree within the driver file. This file tests
// the implementation of various methods of the binary search tree such as
// the methods getHeight, retrieve, insert, bstreeToArray, arrayToBSTree,
// and the overloaded operators.
// ---------------------------------------------------------------------
// Notes - This driver file defines the two global functions buildTree and
// initArray. The buildTree method will read in the strings from the 
// data2.txt input file and inserts these strings into the binary search tree
// until it reads $$ in the input file. The initArray method initializes an
// array of NodeData pointers to null pointers.
// ---------------------------------------------------------------------
#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      // 
void initArray(NodeData*[]);             // initialize array to NULL

int main() {
	// create file object infile and open it
	// for testing, call your data file something appropriate, e.g., data2.txt
	ifstream infile("data2.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	// the NodeData class must have a constructor that takes a string
	NodeData notND("not");
	NodeData andND("and");
	NodeData sssND("sss");
	NodeData ttttND("tttt");
	NodeData oooND("ooo");
	NodeData yND("y");
	NodeData eND("e");
	NodeData mND("m");
	NodeData tND("t");

	BinTree T, T2, dup;
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	cout << "Initial data:" << endl << "  ";
	buildTree(T, infile);              // builds and displays initial data
	cout << endl;
	BinTree first(T);                  // test copy constructor
	dup = dup = T;                     // test operator=, self-assignment
	while (!infile.eof()) {
		cout << "Tree Inorder:" << endl << T;          // operator<< does endl
		T.displaySideways();

		// test retrieve 
		NodeData* p;                    // pointer of retrieved object
		bool found;                     // whether or not object was found in tree
		found = T.retrieve(andND, p);
		cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(notND, p);
		cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(sssND, p);
		cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;

		// test getHeight 
		cout << "Height    --> and:  " << T.getHeight(andND) << endl;
		cout << "Height    --> not:  " << T.getHeight(notND) << endl;
		cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
		cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
		cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
		cout << "Height    --> y:  " << T.getHeight(yND) << endl;

		// test ==, and != 
		T2 = T;
		cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
		cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
		cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
		dup = T;

		// somewhat test bstreeToArray and arrayToBSTree
		T.bstreeToArray(ndArray);
		T.arrayToBSTree(ndArray);
		T.displaySideways();

		T.makeEmpty();                  // empty out the tree
		initArray(ndArray);             // empty out the array

		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "Initial data:" << endl << "  ";
		buildTree(T, infile);
		cout << endl;
	}

	return 0;
}

// ----------------------------------[buildTree]----------------------------------------------
// Description: The buildTree global method reads in the strings from the 
// input file stream until it reaches "$$", which indicates the end of the
// input file. The buildTree method builds the binary search tree with the strings
// that are read in through the input file, each string is a NodeData object in the tree.
// -------------------------------------------------------------------------------------------
void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
		// would do a setData if there were more than a string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}
// -------------------------------------------------------------------------------------------

// ----------------------------------[initArray]----------------------------------------------
// Description: The initArray global method initializes an array of NodeData pointers
// by setting all of the elements in the array equal to nullptr.
// -------------------------------------------------------------------------------------------
void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}
// -------------------------------------------------------------------------------------------
