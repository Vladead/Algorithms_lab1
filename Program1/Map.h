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

		Color c;
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
					c = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(c);
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
					c = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(c);
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

	void setKeys(List<Key>& ls, Node<Key, Value>* node) 
	{
		while (node) 
		{
			setKeys(ls, node->getLeft());
			ls.push_back(node->getKey());
			setKeys(ls, node->getRight());
			return;
		}
	}

	void setValues(List<Value>& ls, Node<Key, Value>* node) 
	{
		while (node) 
		{
			setValues(ls, node->getLeft());
			ls.push_back(node->getValue());
			setValues(ls, node->getRight());
			return;
		}
	}
	 
	Node<Key, Value>* replace(Node<Key, Value>* x) // finds node that replaces a deleted node in BST 
	{
		if (x->getLeft() != nullptr && x->getRight() != nullptr) // when node have 2 children 
			return minValueNode(x->getRight());
 
		if (x->getLeft() == nullptr && x->getRight() == nullptr) // when leaf
			return nullptr;
 
		if (x->getLeft() != nullptr) // when single child
			return x->getLeft();
		else
			return x->getRight();
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

	void swapValues(Node<Key, Value>* u, Node<Key, Value>* v) 
	{
		Key key = u->getKey();
		u->setKey(v->getKey());
		v->setKey(key);
		Value value = u->getValue();
		u->setValue(v->getValue());
		v->setValue(value);
	}
	 
	void deleteNode(Node<Key, Value>* v) // deletes the given node 
	{
		Node<Key, Value>* u = replace(v);
 
		// True when u and v are both black
		bool uvBlack = ((u == nullptr || u->getColor() == black) && (v->getColor() == black));
		Node<Key, Value>* parent = v->getParent();

		if (u == nullptr) 
		{
			// u is nullptr therefore v is leaf 
			if (v == root) {
				// v is root, making root nullptr 
				root = nullptr;
			}
			else 
			{
				if (uvBlack) 
				{
					// u and v both black 
					// v is leaf, fix double black at v 
					fixTree(v);
				}
				else 
				{
					// u or v is red 
					if (v->sibling() != nullptr) 
						v->sibling()->setColor(red); // sibling is not nullptr, make it red
				}

				// delete v from the tree 
				if (v->isOnLeft()) 
				{
					parent->setLeft(nullptr);
				}
				else 
				{
					parent->setRight(nullptr);
				}
			}
			delete v;
			return;
		}
		if (v->getLeft() == nullptr || v->getRight() == nullptr) 
		{
			// v has 1 child 
			if (v == root) 
			{
				// v is root, assign the value of u to v, and delete u 
				v->setKey(u->getKey());
				v->setLeft(nullptr);
				v->setRight(nullptr);
				delete u;
			}
			else 
			{
				// Detach v from tree and move u up 
				if (v->isOnLeft()) 
				{
					parent->setLeft(u);
				}
				else 
				{
					parent->setRight(u);
				}
				delete v;
				u->setParent(parent);
				if (uvBlack) 
				{
					// u and v both black, fix double black at u 
					fixTree(u);
				}
				else 
				{
					// u or v red, color u black 
					u->setColor(black);
				}
			}
			return;
		}
		// v has 2 children, swap values 
		swapValues(u, v);
		deleteNode(u);
	}
	
	void fixTree(Node<Key, Value>* x) // fixes tree after delete
	{
		if (x == root) // Reached root 
			return;

		Node<Key, Value>* sibling = x->sibling(), * parent = x->getParent();
		if (sibling == nullptr) 
		{
			// No sibiling, double black pushed up 
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
				fixTree(x);
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
		Node<Key, Value>* temp = new Node<Key, Value>(key, value);
		if (!root) 
		{
			root = temp;
		}
		else 
		{
			Node<Key, Value>* p = root;
			Node<Key, Value>* q = nullptr;
			while (p != nullptr) 
			{
				q = p;
				if (p->getKey() < temp->getKey()) 
				{
					p = p->getRight();
				}
				else if (p->getKey() == temp->getKey())
				{
					throw invalid_argument("This element is already in the map");
				}
				else 
				{
					p = p->getLeft();
				}
			}
			temp->setParent(q);
			if (q->getKey() <= temp->getKey()) 
			{
				q->setRight(temp);
			}
			else 
			{
				q->setLeft(temp);
			}
		}
		balanceTree(temp);
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