#pragma once

#include <iostream>
#include "Node.h"
#include "List.h"
#include "windows.h"

using namespace std;

template <typename Key, typename Value>
class Map
{
private:
	Node<Key, Value>* root;
	
	void SetColor(int text, int background) // Set color in console
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
	}

	void balanceTree(Node<Key, Value>*& node) // Balance tree
	{
		if (root == node)
		{
			node->setColor(black);
			return;
		}

		Color color;
		Node<Key, Value>* parent = nullptr, * grandparent = nullptr, * uncle = nullptr;

		while (node != root && node->getColor() == red && node->getParent()->getColor() == red)
		{
			parent = node->getParent();
			grandparent = parent->getParent();
			if (parent == grandparent->getLeft())
			{
				uncle = grandparent->getRight();
				if (uncle->getColor() == red)
				{
					parent->setColor(black);
					grandparent->setColor(red);
					uncle->setColor(black);
					node = grandparent;
				}
				else
				{
					if (node == parent->getRight())
					{
						leftRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					rightRotate(grandparent);
					color = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(color);
					node = parent;
				}
			}
			else
			{
				uncle = grandparent->getLeft();
				if (uncle->getColor() == red)
				{
					parent->setColor(black);
					grandparent->setColor(red);
					uncle->setColor(black);
					node = grandparent;
				}
				else
				{
					if (node == parent->getLeft())
					{
						rightRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					leftRotate(grandparent);
					color = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(color);
					node = parent;
				}
			}
		}
		root->setColor(black);
	}

	Node<Key, Value>* minValueNode(Node<Key, Value>* node) // Retunrs the most left element
	{
		Node<Key, Value>* ptr = node;

		while (ptr->getLeft() != nullptr)
		{
			ptr = ptr->getLeft();
		}

		return ptr;
	}

	void leftRotate(Node<Key, Value>* node) 
	{
		Node<Key, Value>* right_child = node->getRight();
		node->setRight(right_child->getLeft());

		if (node->getRight() != nullptr)
			node->getRight()->setParent(node);

		right_child->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = right_child;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(right_child);
		else
			node->getParent()->setRight(right_child);

		right_child->setLeft(node);
		node->setParent(right_child);
	}

	void rightRotate(Node<Key, Value>* node) 
	{
		Node<Key, Value>* left_child = node->getLeft();
		node->setLeft(left_child->getRight());

		if (node->getLeft() != nullptr)
			node->getLeft()->setParent(node);

		left_child->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = left_child;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(left_child);
		else
			node->getParent()->setRight(left_child);

		left_child->setRight(node);
		node->setParent(left_child);
	}

	void delSubTree(Node<Key, Value>* node)	// Auxiliary function for deleting map
	{
		while (node != nullptr) 
		{
			delSubTree(node->getLeft());
			delSubTree(node->getRight());
			delete node;
			node = nullptr;
		}
		root = nullptr;
	}
	
	void print_node(Node<Key, Value>* node, int level, bool side) // Auxiliary function for output
	{
		for (int i = 0; i < level; i++)
			cout << ' ';
		if (level != 0)
		{
			cout << '|';
			cout << "->";
			if (side == false)
				cout << "L: ";
			else
				cout << "R: ";
		}
		else
			cout << ' ';
		if (node) 
		{
			if (node->getColor() == black || node->getColor() == black)
				SetColor(9, 0);
			else
				SetColor(12, 0);
			cout << node->getKey() << '(' << node->getValue() << ')' << endl;
			SetColor(7, 0);
		}
		else 
		{
			SetColor(9, 0);
			cout << "nil" << endl;
			SetColor(7, 0);
		}
		if (node)
		{
			if (level > 0)
			{
				if (node->getLeft() || node->getRight())
				{
					print_node(node->getLeft(), level + 3, false);
					print_node(node->getRight(), level + 3, true);
				}
			}
			else
			{
				if (node->getLeft() || node->getRight())
				{
					print_node(node->getLeft(), level + 1, false);
					print_node(node->getRight(), level + 1, true);
				}
			}
		}
	}

	void setKeys(List<Key>& key, Node<Key, Value>* node) 
	{
		while (node) 
		{
			setKeys(key, node->getLeft());
			key.push_back(node->getKey());
			setKeys(key, node->getRight());
			return;
		}
	}

	void setValues(List<Value>& value, Node<Key, Value>* node) 
	{
		while (node) 
		{
			setValues(value, node->getLeft());
			value.push_back(node->getValue());
			setValues(value, node->getRight());
			return;
		}
	}
	 
	Node<Key, Value>* replace(Node<Key, Value>* node) // finds node that replaces a deleted node in BST 
	{
		if (node->getLeft() != nullptr && node->getRight() != nullptr) // when node have 2 children 
			return minValueNode(node->getRight());
 
		if (node->getLeft() == nullptr && node->getRight() == nullptr) // when leaf
			return nullptr;
 
		if (node->getLeft() != nullptr) // when single child
			return node->getLeft();
		else
			return node->getRight();
	}
	 
	Node<Key, Value>* search(Key key) // returns pointer to element with required key 
	{
		Node<Key, Value>* temp = root;
		while (temp != NULL && key != temp->getKey()) 
		{
			if (key < temp->getKey()) 
			{
				temp = temp->getLeft();
			}
			else 
			{
				temp = temp->getRight();
			}
		}
		return temp;
	}

	void swapValues(Node<Key, Value>* firstNode, Node<Key, Value>* secondNode) 
	{
		Key key = firstNode->getKey();
		firstNode->setKey(secondNode->getKey());
		secondNode->setKey(key);
		Value value = firstNode->getValue();
		firstNode->setValue(secondNode->getValue());
		secondNode->setValue(value);
	}
	 
	void deleteNode(Node<Key, Value>* deletedNode) // deletes the given node 
	{
		Node<Key, Value>* temp = replace(deletedNode);
 
		// True when temp and deletedNode are both black
		bool uvBlack = ((temp == nullptr || temp->getColor() == black) && (deletedNode->getColor() == black));
		Node<Key, Value>* parent = deletedNode->getParent();

		if (temp == nullptr) 
		{
			// temp is nullptr therefore deletedNode is leaf 
			if (deletedNode == root) {
				// deletedNode is root, making root nullptr 
				root = nullptr;
			}
			else 
			{
				if (uvBlack) 
				{
					// temp and deletedNode both black 
					// deletedNode is leaf, fix double black at deletedNode 
					fixTree(deletedNode);
				}
				else 
				{
					// temp or deletedNode is red 
					if (deletedNode->sibling() != nullptr) 
						deletedNode->sibling()->setColor(red); // sibling is not nullptr, make it red
				}

				// delete deletedNode from the tree 
				if (deletedNode->isOnLeft()) 
				{
					parent->setLeft(nullptr);
				}
				else 
				{
					parent->setRight(nullptr);
				}
			}
			delete deletedNode;
			return;
		}
		if (deletedNode->getLeft() == nullptr || deletedNode->getRight() == nullptr) 
		{
			// deletedNode has 1 child 
			if (deletedNode == root) 
			{
				// deletedNode is root, assign the value of temp to deletedNode, and delete temp 
				deletedNode->setKey(temp->getKey());
				deletedNode->setLeft(nullptr);
				deletedNode->setRight(nullptr);
				delete temp;
			}
			else 
			{
				// Detach deletedNode from tree and move temp up 
				if (deletedNode->isOnLeft()) 
				{
					parent->setLeft(temp);
				}
				else 
				{
					parent->setRight(temp);
				}
				delete deletedNode;
				temp->setParent(parent);
				if (uvBlack) 
				{
					// temp and deletedNode both black, fix double black at temp 
					fixTree(temp);
				}
				else 
				{
					// temp or deletedNode red, color temp black 
					temp->setColor(black);
				}
			}
			return;
		}
		// deletedNode has 2 children, swap values 
		swapValues(temp, deletedNode);
		deleteNode(temp);
	}
	
	void fixTree(Node<Key, Value>* rootNode) // fixes tree after delete
	{
		if (rootNode == root) // Reached root 
			return;

		Node<Key, Value>* sibling = rootNode->sibling(), * parent = rootNode->getParent();
		if (sibling == nullptr) 
		{
			// No sibiling, black pushed up 
			fixTree(parent);
		}
		else 
		{
			if (sibling->getColor() == red) 
			{
				// Sibling red 
				parent->setColor(red);
				sibling->setColor(black);
				if (sibling->isOnLeft())
				{
					// left case 
					rightRotate(parent);
				}
				else 
				{
					// right case 
					leftRotate(parent);
				}
				fixTree(rootNode);
			}
			else 
			{
				// Sibling black 
				if (sibling->hasRedChild()) 
				{
					// at least 1 red children 
					if (sibling->getLeft() != nullptr && sibling->getLeft()->getColor() == red) 
					{
						if (sibling->isOnLeft()) 
						{
							// left left 
							sibling->getLeft()->setColor(sibling->getColor());
							sibling->setColor(parent->getColor());
							rightRotate(parent);
						}
						else 
						{
							// right left 
							sibling->getLeft()->setColor(parent->getColor());
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else 
					{
						if (sibling->isOnLeft()) 
						{
							// left right 
							sibling->getRight()->setColor(parent->getColor());
							leftRotate(sibling);
							rightRotate(parent);
						}
						else 
						{
							// right right 
							sibling->getRight()->setColor(sibling->getColor());
							sibling->setColor(parent->getColor());
							leftRotate(parent);
						}
					}
					parent->setColor(black);
				}
				else 
				{
					// 2 black children 
					sibling->setColor(red);
					if (parent->getColor() == black)
						fixTree(parent);
					else
						parent->setColor(black);
				}
			}
		}
	}

public:
	Map() : root(nullptr) {}
	
	~Map() 
	{
		delSubTree(root);
	}

	void insert(Key key, Value value) //Inserts node using key with value 
	{
		Node<Key, Value>* insertedNode = new Node<Key, Value>(key, value);
		if (!root) 
		{
			root = insertedNode;
		}
		else 
		{
			Node<Key, Value>* rootNode = root;
			Node<Key, Value>* temp = nullptr;
			while (rootNode != nullptr) 
			{
				temp = rootNode;
				if (rootNode->getKey() < insertedNode->getKey()) 
				{
					rootNode = rootNode->getRight();
				}
				else if (rootNode->getKey() == insertedNode->getKey())
				{
					throw invalid_argument("This element is already in the map");
				}
				else 
				{
					rootNode = rootNode->getLeft();
				}
			}
			insertedNode->setParent(temp);
			if (temp->getKey() <= insertedNode->getKey()) 
			{
				temp->setRight(insertedNode);
			}
			else 
			{
				temp->setLeft(insertedNode);
			}
		}
		balanceTree(insertedNode);
	}

	void remove(Key key) //Removes an element 
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty");

		Node<Key, Value>* node = search(key);

		if (node->getKey() != key) 
		{
			throw invalid_argument("This element isn't in the map");
		}

		deleteNode(node);
	}

	Value find(Key key) //Returns the value using key 
	{
		if (!root)
			throw invalid_argument("Map is empty");
		
		Node<Key, Value>* temp = root;

		while (temp && temp->getKey() != key) 
		{
			if (temp->getKey() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		if (!temp)
			throw invalid_argument("This element isn't in the map");
		
		return temp->getValue();
	}

	void clear() //Cleans the map 
	{
		if (root == nullptr)
			throw runtime_error("The map is empty");
		delSubTree(root);
	}

	List<Key> get_keys() //Returns a copy of list that contains keys of map
	{
		List<Key> ls;
		setKeys(ls, root);
		return ls;
	}

	List<Value> get_values() //Returns a copy of list that contains values of map
	{
		List<Value> ls;
		setValues(ls, root);
		return ls;
	}

	void print() //Prints red-black map
	{
		if (root == nullptr)
			throw runtime_error("Map is empty");
		int level = 0;
		print_node(root, level, false);
		cout << endl;
	}
};