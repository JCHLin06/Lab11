#pragma once

class Node
{
private:
	int m_value;
	Node * m_next;

public:
	Node() = delete;
	Node(int val);
	Node(int val, Node * nextNode);
	void setItem(const int& val);
	void setNext(Node* nextNodePtr);
	int getItem() const;
	Node * getNext() const;
	virtual ~Node();
	
};