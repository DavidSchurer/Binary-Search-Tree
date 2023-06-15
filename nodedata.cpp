// ---------------------------- nodedata.cpp ---------------------------
// David Schurer
// CSS 343
// Creation Date: 4/12/2023
// Date of Last Modification: 4/20/2023
// ---------------------------------------------------------------------
// Purpose - The nodedata.cpp file is the implementation file that provides
// the implementation of all the methods of the NodeData class. This class
// represents the string data that is stored within each node in the binary
// search tree.
// ---------------------------------------------------------------------
// Notes - This NodeData class implements the use of operator overloading
// as it has overloaded operators for =, ==, !=, <, >, <=, and >=. These
// operators allow for the comparison of NodeData objects.
// ---------------------------------------------------------------------
#include "nodedata.h"
#include <iostream>
using namespace std;

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData() { data = ""; }                         // default

NodeData::~NodeData() { }            // needed so strings are deleted properly

NodeData::NodeData(const NodeData& nd) { data = nd.data; }  // copy

NodeData::NodeData(const string& s) { data = s; }    // cast string to NodeData

//------------------------- operator= ----------------------------------------
NodeData& NodeData::operator=(const NodeData& rhs) {
	if (this != &rhs) {
		data = rhs.data;
	}
	return *this;
}

//------------------------- operator==,!= ------------------------------------
bool NodeData::operator==(const NodeData& rhs) const {
	return data == rhs.data;
}

bool NodeData::operator!=(const NodeData& rhs) const {
	return data != rhs.data;
}

//------------------------ operator<,>,<=,>= ---------------------------------
bool NodeData::operator<(const NodeData& rhs) const {
	return data < rhs.data;
}

bool NodeData::operator>(const NodeData& rhs) const {
	return data > rhs.data;
}

bool NodeData::operator<=(const NodeData& rhs) const {
	return data <= rhs.data;
}

bool NodeData::operator>=(const NodeData& rhs) const {
	return data >= rhs.data;
}

//------------------------------ setData -------------------------------------
// returns true if the data is set, false when bad data, i.e., is eof

bool NodeData::setData(istream& infile) {
	getline(infile, data);
	return !infile.eof();       // eof function is true when eof char is read
}

//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
	output << nd.data;
	return output;
}
