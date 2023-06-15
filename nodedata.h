// ----------------------------- nodedata.h ----------------------------
// David Schurer
// CSS 343
// Creation Date: 4/12/2023
// Date of Last Modification: 4/20/2023
// ---------------------------------------------------------------------
// Purpose - The nodedata.h file is the header file for the node data
// of each node that is stored in the binary search tree. This class
// has several constructors and a destructor as well as overloaded operator
// methods that are used to compare NodeData objects.
// ---------------------------------------------------------------------
// Notes - This class uses comparison algorithms such as the overloaded
// operators to compare data stored in two instances of the class, this
// class also uses the setData() to read in input from a text file
// and it returns true if the data is set successfully or false if
// the data is bad or the input stream reaches the end-of-file before
// reading in any data.
// ---------------------------------------------------------------------
#ifndef NODEDATA_H
#define NODEDATA_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// simple class containing one string to use for testing
// not necessary to comment further

class NodeData {
	friend ostream & operator<<(ostream &, const NodeData &);

public:
	NodeData();          // default constructor, data is set to an empty string
	~NodeData();
	NodeData(const string &);      // data is set equal to parameter
	NodeData(const NodeData &);    // copy constructor
	NodeData& operator=(const NodeData &);

	// set class data from data file
	// returns true if the data is set, false when bad data, i.e., is eof
	bool setData(istream&);

	bool operator==(const NodeData &) const;
	bool operator!=(const NodeData &) const;
	bool operator<(const NodeData &) const;
	bool operator>(const NodeData &) const;
	bool operator<=(const NodeData &) const;
	bool operator>=(const NodeData &) const;

private:
	string data;
};

#endif
