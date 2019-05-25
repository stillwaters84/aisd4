#include <iostream>
#include "mylist.h"
//#include "HuffTree.h"
///need to fix everything from private in class to methods and variables
using namespace std;

template <class T, class V> class Map;
template <class T, class V> class Node;

/** 3 types of exceptions:
1) Left son true parent true Uncle:
Just repaint the nodes
2) Right son true parent false Uncle:
repaint nodes then rotate Left
3) Left son true parent false Uncle:
repaint nodes then rotate Right
*/
template <class T, class V>
class Map{ ///put classes fields in private
private:
	void LeftRotate(Node<T,V>* x);
	void RightRotate(Node<T,V>* x);
	void insertFix(Node<T,V>* newNode); ///private
	void FixDelete(Node<T,V>* current, Node<T,V>* fixParent); ///private
public:
    Node<T,V> *root;
	size_t size;
    //size_t falseHeight;
    Map();
    void insertnode(T key, V value);
    //MyList<HuffLeaf*> TravelMap();
    int FindNode(T key);
	//int Find_ID(V value);
    void DeleteNode(T key);
    void Clear();
	MyList<T>* get_keys();
	void get_keys_node(MyList<T> *keyList, Node<T,V> *root);
	MyList<V>* get_values();
	void get_keys_value(MyList<V>* valueList, Node<T, V>* root);
	Node<T, V>* getRoot();
	size_t get_size() { return size; }
	//friend class HuffLeaf;
};

template <class T, class V>
Node <T, V>* Map<T, V>::getRoot() {
	return root;
}

template <class T, class V>
MyList<T> *Map<T,V>::get_keys() {
	MyList<T>* keyList = new MyList<T>();
	Node<T, V>* starting_point = root;
	get_keys_node(keyList, starting_point);
	return keyList;
}


template <class T, class V>
void Map<T, V>::get_keys_node(MyList<T> *keyList, Node<T,V> *root) {
	if (root != nullptr) {
		get_keys_node(keyList, root->left);
		keyList->push_back(root->key);
		get_keys_node(keyList, root->right);
	}
}

template <class T, class V>
MyList<V>* Map<T, V>::get_values() {
	MyList<V>* valueList = new MyList<V>();
	Node<T, V>* starting_point = root;
	get_keys_value(valueList, starting_point);
	return valueList;
}


template <class T, class V>
void Map<T, V>::get_keys_value(MyList<V>* valueList, Node<T, V>* root) {
	if (root != nullptr) {
		get_keys_value(valueList, root->left);
		valueList->push_back(root->value);
		get_keys_value(valueList, root->right);
	}
}
template <class T, class V>
class Node {
private:
	bool color;
	bool getColor();
	void clearNode();
public:
	Node* right;
	Node* left;
	Node* parent;
	V value;
	T key;
	Node();
	Node(T key, V value, Node* parent);
	~Node();
	//MyList<T>* get_keys_nodes(Node<T, V>* root);
	friend class Map<T, V>;
};


template <class T, class V>
Node<T, V>::Node() {
	this->right = nullptr;
	this->left = nullptr;
	this->parent = nullptr;
	//this->key = 0;
	this->color = false;
}

template <class T, class V>
Node<T, V>::Node(T key, V value, Node<T, V>* parent) {
	this->right = nullptr;
	this->left = nullptr;
	this->parent = parent;
	this->key = key;
	this->value = value;
	this->color = true;
}

template <class T, class V>
Node<T, V>::~Node() {
	this->right = nullptr;
	this->left = nullptr;
	this->parent = nullptr;
	this->key = 0;
	this->value = 0;
	this->color = false;
}

template <class T, class V>
void Node<T, V>::clearNode() {
	if (this != nullptr) {
		left->clearNode();
		right->clearNode();
		delete this;
	}
}

template <class T, class V>
bool Node<T, V>::getColor() {
	if (this != nullptr) {
		return this->color;
	}
	else
		return false;
}

template <class T, class V>
Map<T, V>::Map() {
	this->root = nullptr;
	root = nullptr;
	size = 0;
	//falseHeight = 0;
}
///make destructor to a tree

///LeftRotate
template <class T, class V>
void Map<T, V>::LeftRotate(Node<T, V>* fixingNode) {
	Node<T, V>* rightSon = fixingNode->right;
	fixingNode->right = rightSon->left;
	if (rightSon->left != nullptr) {
		rightSon->left->parent = fixingNode;
	}
	if (rightSon != nullptr) {
		rightSon->parent = fixingNode->parent;
	}
	if (fixingNode->parent != nullptr) {
		if (fixingNode == fixingNode->parent->left) {
			fixingNode->parent->left = rightSon;
		}
		else {
			fixingNode->parent->right = rightSon;
		}
	}
	else {
		root = rightSon;
	}
	rightSon->left = fixingNode;
	if (fixingNode != nullptr) {
		fixingNode->parent = rightSon;
	}
}

template <class T, class V>
void Map<T, V>::RightRotate(Node<T, V> * x) {
	Node<T, V>* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	if (y != nullptr) {
		y->parent = x->parent;
	}
	if (x->parent != nullptr) {
		if (x == x->parent->right) {
			x->parent->right = y;
		}
		else
			x->parent->left = y;
	}
	else {
		root = y;
	}
	y->right = x;
	if (x != nullptr) {
		x->parent = y;
	}
}

template <class T, class V>
void Map<T, V>::insertFix(Node<T, V> * newNode) {
	Node<T, V>* uncle;
	while (newNode != root && newNode->parent->color == true) {
		if (newNode->parent == newNode->parent->parent->left) { ///left subtree
			if (newNode->parent->parent->right == nullptr) ///if grandfather doesn't exist
				uncle = new Node<T, V>();
			else
				uncle = newNode->parent->parent->right; ///uncle is right son of grandfather
			if (uncle->color == true) {
				newNode->parent->color = false;
				uncle->color = false;
				newNode->parent->parent->color = true;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->right) {
					newNode = newNode->parent;
					LeftRotate(newNode); ///if uncle color is false and node is right son
				}

				newNode->parent->color = false;
				newNode->parent->parent->color = true;
				RightRotate(newNode->parent->parent); ///when parent is false and grandfather is true
			}
		}
		else {
			if (newNode->parent->parent->left == nullptr)
				uncle = new Node<T, V>();
			else
				uncle = newNode->parent->parent->left;
			if (uncle->color == true) {
				newNode->parent->color = false;
				uncle->color = false;
				newNode->parent->parent->color = true;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->left) {
					newNode = newNode->parent;
					RightRotate(newNode);
				}
				newNode->parent->color = false;
				newNode->parent->parent->color = true;
				LeftRotate(newNode->parent->parent);
			}
		}
	}
	root->color = false;
}

template <class T, class V>
void Map<T, V>::insertnode(T key, V value) {
	Node<T, V>* current, * parent, * newNode;
	current = root;
	parent = nullptr;
	while (current != nullptr) {   ///find where to insert
		parent = current;
		if (key < current->key) {
			current = current->left;
		}
		else
			current = current->right;
		}
	newNode = new Node<T, V>(key, value, parent); ///set up new Node

	if (parent != nullptr) {  ///insert node in tree
		if (key < parent->key) {
			parent->left = newNode;
		}
		else
			parent->right = newNode;
	}
	else {
		root = newNode;
	}
	insertFix(newNode);
	size++;
}
///pushback only one elem
/*template <class T, class V>
MyList<HuffLeaf*> Map<T, V>::TravelMap() { 
	MyList<HuffLeaf*> HuffList;
	auto keys = get_keys();
	auto values = get_values();
	auto curr_key = keys->first; 
	auto curr_val = values->first;

	while (curr_key){
		HuffList.push_back(new HuffLeaf({curr_key->number}, curr_val->number));
		curr_key = curr_key->next;
		curr_val = curr_val->next;
	}
	return HuffList;
}*/

template <class T, class V>
int Map<T, V>::FindNode(T key) {
	Node<T, V>* current = root;
	while (current != nullptr) {
		if (key == current->key) {
			return current->value;
		}
		else {
			if (key < current->key) {
				current = current->left;
			}
			else
				current = current->right;
		}
	}
	return -1; ///make an exception
}


template <class T, class V>
void Map<T, V>::DeleteNode(T key) {
	Node<T, V>* deleteObj, * newNode2; ///temporary variables
	Node<T, V>* current = FindNode(key);
	if (current == nullptr) {
		throw out_of_range("Empty");
	}
	if (current->left == nullptr || current->right == nullptr) {
		deleteObj = current;
	}
	else {
		deleteObj = current->right;
		while (deleteObj->left != nullptr) deleteObj = deleteObj->left;
	}

	if (deleteObj->left != nullptr) {
		newNode2 = deleteObj->left;
	}
	else if (deleteObj->right != nullptr) {
		newNode2 = deleteObj->right;
	}
	else
		newNode2 = nullptr;

	if (deleteObj->parent != nullptr) {
		if (newNode2 != nullptr) {
			newNode2->parent = deleteObj->parent;
		}
		if (deleteObj == deleteObj->parent->left) {
			deleteObj->parent->left = newNode2;
		}
		else
			deleteObj->parent->right = newNode2;
	}
	else newNode2 = root;

	if (deleteObj != current) {
		current->key = deleteObj->key;
	}
	if (deleteObj->color == false) {
		FixDelete(newNode2, deleteObj->parent);
	}
	delete deleteObj;
	size--;
}

template <class T, class V>
void Map<T, V>::FixDelete(Node<T, V>* current, Node<T, V>* fixParent) {
	///maybe there's no current->parent->left/right
	while (current != root && current->getColor() == false) {
		if (current == fixParent->left) {
			Node<T, V>* temp = fixParent->right;
			if (temp->getColor() == true) {
				temp->color = false;
				fixParent->color = true;
				LeftRotate(fixParent);
				temp = fixParent->right;
			}
			if (temp->left->getColor() == false && temp->right->getColor() == false) {
				temp->color = true;
				current = fixParent;
			}
			else {
				if (temp->right->color == false) {
					temp->left->color = false;
					temp->color = true;
					RightRotate(temp);
					temp = fixParent->right;
				}
				temp->color = fixParent->color;
				fixParent->color = false;
				current->color = false;
				LeftRotate(fixParent);
				current = root;
			}
		}
		else {
			Node<T, V>* temp = fixParent->left;
			if (temp->color == true) {
				temp->color = false;
				fixParent->color = true;
				RightRotate(fixParent);
				temp = fixParent->left;
			}
			///there is no temp->right
			if (temp->right->getColor() == false && temp->left->getColor() == false) {
				temp->color = true;
				current = fixParent;
			}
			else {
				if (temp->left->color == false) {
					if (temp->right != nullptr) {
						temp->right->color = false;
					}
					temp->color = true;
					LeftRotate(temp);
					temp = fixParent->left;
				}
				temp->color = fixParent->color;
				fixParent->color = false;
				temp->left->color = false;
				RightRotate(fixParent);
				current = root;
			}
		}
	}
}

template <class T, class V>
void Map<T, V>::Clear() { ///Recursive In-Order Travers
	root->clearNode();
	root = nullptr;
}
///remove doesn't working anymore
///get keys & get values - push_back from 1 laba and recursive travers
///tests: insert(1,1); newNode = find(1); assert(newNode->key == 1) - good
///remove test - if exception then good (catch "exceptions", exceptions.what()
