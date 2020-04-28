#pragma once

enum Color {
	black,
	red
};

template <typename Key, typename Value>
class Node
{
private:
	Color color;
	Node<Key, Value> *left, *right, *parent;
	Key key;
	Value value;
public:
	Node() : color(red), left(nullptr), right(nullptr), parent(nullptr)
	{
	
	}
	
	Node(Key key, Value value) : color(red), left(nullptr), right(nullptr), parent(nullptr), key(key), value(value) 
	{

	}

	bool isOnLeft()
	{
		return this == parent->getLeft();
	}

	Node<Key, Value>* sibling()
	{
		if (parent == nullptr)	// If there is no parent then sibling is null
		{
			return nullptr;
		}

		if (isOnLeft())
		{
			return parent->getRight();
		}

		return parent->getLeft();
	}

	bool hasRedChild()
	{
		return (left != nullptr && left->getColor() == red) ||
			(right != nullptr && right->getColor() == red);
	}

	void setColor(Color color)
	{
		this->color = color;
	}

	Color getColor()
	{
		if (this == nullptr)
		{
			return black;
		}
		return color;
	}

	void setLeft(Node* ptr)
	{
		left = ptr;
	}

	Node* getLeft()
	{
		return left;
	}

	void setRight(Node* ptr)
	{
		right = ptr;
	}

	Node* getRight()
	{
		return right;
	}

	void setParent(Node* parent)
	{
		this->parent = parent;
	}

	Node* getParent()
	{
		return parent;
	}

	void setKey(Key key)
	{
		this->key = key;
	}

	Key getKey()
	{
		return key;
	}

	void setValue(Value value)
	{
		this->value = value;
	}

	Value getValue()
	{
		return value;
	}
};