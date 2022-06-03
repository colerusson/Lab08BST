
#ifndef BST_H
#define BST_H
#include "BSTInterface.h"
#include <string>

using namespace std;

template<typename T>
class BST : public BSTInterface<T> {
private:
	struct Node {		//Node struct nested within the BST template class
		struct Node* left_;		//left and right nodes to use in a tree
		struct Node* right_;
		T data_;
		int level_;

		Node(T data, Node* left = NULL, Node* right = NULL) :		//constructor for struct node, passing in data and setting left and right to NULL
			data_(data), left_(left), right_(right), level_(0) {}
		~Node() = default;

		friend ostream& operator<<(ostream& os, const struct Node* node) {		//friend operator to print out data
			os << node->data_;
			return os;
		}
	};
	Node* root;		//head or root node of the tree

	bool insert(Node*& node, const T& data) {		//insert recursive function which is called from the public section of BST class
		if (node == NULL) {
			node = new Node(data);
			return true;
		}
		if (data < node->data_) return insert(node->left_, data);
		if (data > node->data_) return insert(node->right_, data);
		return false;
	}

	bool deleteNode(Node*& node, const T& data) {		//delete item recursive function which is called from the public section of BST class
		if (node == NULL) return false;
		if (data < node->data_) return deleteNode(node->left_, data);
		if (data > node->data_) return deleteNode(node->right_, data);

		Node* oldNode = node;
		if (node->left_ == NULL) node = node->right_;		
		else if (node->right_ == NULL) node = node->left_;	
		else {
			Node* predecessor = node->left_;		
			while (predecessor->right_ != NULL) predecessor = predecessor->right_;
			swap(node->data_, predecessor->data_);
			deleteNode(node->left_, data);
			return true;
		}
		delete oldNode;
		return true;
	} 

	bool find(Node* node, const T& value) {		//find recursive function which is called from the public section of BST class
		if (node == NULL) return false;
		if (node->data_ == value) return true;
		if (value < node->data_) return find(node->left_, value);
		return find(node->right_, value);
	}

	bool deleteTree(Node* node) {		//clear tree recursive function which is called from the public section of BST class
		if (node == NULL) return false;
		deleteTree(node->left_);
		deleteTree(node->right_);
		delete node;
		root = NULL;
		return true;
	}

	int size(Node* node) {		//size recursive function which is called from the public section of BST class
		if (node == NULL) {
			return 0;
		}
		else {
			return(size(node->left_) + 1 + size(node->right_));
		}
	}

	void copyTree(Node*& nodeCopy, Node*& nodeOther) {	//copy recursive function which is called from the public section of BST class
		if (nodeOther == NULL) {
			nodeCopy = NULL;
		}
		else {
			nodeCopy = new Node(nodeOther->data_);
			copyTree(nodeCopy->left_, nodeOther->left_);
			copyTree(nodeCopy->right_, nodeOther->right_);
		}
	}

public:
	BST() : root(NULL) {}		//constructor for BST object, setting root equal to NULL
	~BST() {
		clearTree();			//deep destructor to remove memory leaks
	}

	virtual bool addNode(const T& data) {		//addNode function which calls a recursive function in the private section 
		return insert(root, data);
	}

	virtual bool removeNode(const T& data) {	//removeNode function which calls a recursive function in the private section
		deleteNode(root, data);
		return true;
	}

	virtual bool clearTree() {		//clearTree function which calls a recursive function in the private section
		return deleteTree(root);
	}

	bool findValue(const T& value) {		//findValue function which calls a recursive function in the private section
		return find(root, value);
	}

	int sizeTree() {		//sizeTree function which calls a recursive function in the private section
		return size(root);
	}

	bool outLevel(Node* root, int level, stringstream& out) const {		//function whihc handles level order output of the tree
		if (root == NULL) return false;
		if (level == 1) {
			out << " " << root->data_;
			if ((root->left_ != NULL) || (root->right_ != NULL)) return true;
			return false;
		}
		if ((level == 2) && !root->left_ && root->right_) out << " _";
		bool left = outLevel(root->left_, level - 1, out);
		bool right = outLevel(root->right_, level - 1, out);
		if ((level == 2) && root->left_ && !root->right_) out << " _";
		return left || right;
	} 

	virtual string toString() const {		//toString function which calls the outLevel recursive function to output level order of the tree
		stringstream out;
		if (root == NULL) out << " empty";
		else {
			int level = 0;
			do {
				out << endl << "  " << ++level << ":";
			} while (outLevel(root, level, out));
		}
		return out.str();
	} 

	BST<T>(BST<T>& other) {		//deep copy constructor for the class, which calls the recursive copyTree function in private
		if (other.root == NULL) {
			this->root = NULL;
		}
		else {
			copyTree(this->root, other.root);
		}
		return;
	}

	BST<T>& operator=(BST<T>& other) {		//deep assignment operator, which calls the deep copy constructor 
		BST<T> newTree(other);
		swap(newTree.root, root);
		return *this;
	}
};
#endif	// BST_INTERFACE_H

