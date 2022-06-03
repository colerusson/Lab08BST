#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "BST.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif		

int main(int argc, char* argv[]) {
	VS_MEM_CHECK	//implementing memory check

		if (argc < 3) {
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	BST<string> bstString;			//instantiations of BST objects with int, string, and copies of each
	BST<string> bstStringCopy;
	BST<int> bstInt;
	BST<int> bstIntCopy;	
	bool intVal = true;		//bool to determine if we are in int or string mode
	bool haveAdded = false;		//bool to determine if we have added to any tree yet

	for (string line; getline(in, line);) {		//parse through the file until the end
		string item1, stringItem;
		int intItem;
		if (line.size() == 0) continue;
		out << endl << line;
		istringstream iss(line);
		iss >> item1;
		if (item1 == "INT") {		//if int is called, set the bool to int mode and mark that we have added 
			haveAdded = true;
			intVal = true;
			out << " OK";
		}
		else if (item1 == "STRING") {		//if string is called, set the bool to string mode by declaring false
			haveAdded = true;
			intVal = false;
			out << " OK";
		}
		else if (item1 == "add") {		//if add is called, check for which mode we are in, then add the node to the tree
			if (intVal == true) {
				iss >> intItem;
				if (bstInt.addNode(intItem) == true) {
					out << " OK";
				}
				else {
					out << " Error";
				}
				haveAdded = true;
			}
			else {
				iss >> stringItem;
				if (bstString.addNode(stringItem) == true) {
					out << " OK";
				}
				else {
					out << " Error";
				}
				haveAdded = true;
			}
		}
		else if (item1 == "print") {		//if print is called, check for which mode we are in, then call the toString for the respective tree
			if (haveAdded == true) {
				if (intVal == true) {
					out << bstInt.toString();
				}
				else {
					out << bstString.toString();
				}
			}
			else {
				out << " Error";
			}
		}
		else if (item1 == "find") {		//if find is called, check for which mode we are in, then call find on the respective object
			if (intVal == true) {
				iss >> intItem;
				if (bstInt.findValue(intItem) == true) {
					out << " found";
				}
				else {
					out << " not found";
				}
			}
			else {
				iss >> stringItem;
				if (bstString.findValue(stringItem) == true) {
					out << " found";
				}
				else {
					out << " not found";
				}
			}
		}
		else if (item1 == "size") {		//if size is called, check for which mode we are in and call for the size of the respective tree
			if (intVal == true) {
				out << " " << bstInt.sizeTree();
			}
			else {
				out << " " << bstString.sizeTree();
			}
		}
		else if (item1 == "clear") {		//if clear is called, check for which mode we are in and call clear for the respective tree
			if (intVal == true) {
				bstInt.clearTree();
			}
			else {
				bstString.clearTree();
			}
			out << " OK";
		}
		else if (item1 == "remove") {		//if remove is called, check for which mode we are in and call remove for the item in the respective tree
			if (intVal == true) {
				iss >> intItem;
				if (bstInt.findValue(intItem) == true) {
					bstInt.removeNode(intItem);
					out << " OK";
				}
				else {
					out << " Error";
				}
			}
			else {
				iss >> stringItem;
				if (bstString.findValue(stringItem) == true) {
					bstString.removeNode(stringItem);
					out << " OK";
				}
				else {
					out << " Error";
				}
			}
		}
		else if (item1 == "copy") {		//if copy is called, check for which mode we are in and call the deep copy assignment operator for the object
			if (intVal == true) {
				if (bstInt.sizeTree() == 0) {
					out << " Error";
				}
				else {
					bstIntCopy = bstInt;
					out << " OK";
				}
			}
			else {
				if (bstString.sizeTree() == 0) {
					out << " Error";
				}
				else {
					bstStringCopy = bstString;
					out << " OK";
				}
			}
		}
		else if (item1 == "printcopy") {		//if printcopy is called, check for which mode we are in and call the to string on the copied object
			if (intVal == true) {
				out << bstIntCopy.toString();
			}
			else {
				out << bstStringCopy.toString();
			}
		}
	}

	in.close();
	return 0;
}
