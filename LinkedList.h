#pragma once

#include <string>
#include "Node.h"


class  IList {
public:

	IList();

	/** Returns true  if list is empty, otherwise false */
	virtual bool isEmpty() const ;
	/** Returns the number of elements in the LinkedList */
	virtual int getSize() const;

	/** Adds a value to the LinkedList.  Adds the value to the end of the List.  Return true if able to, otherwise false */
	virtual bool add(int val) = 0;
	/** Remove a value to the LinkedList.  Return true if able to, otherwise false.
	Will only remove one entry if there are multiple entries with the same value */
	virtual bool remove(int val) = 0;
	/** Remove  all elements from LinkedList */
	virtual void clear() = 0;
        /** Generates a string of the contents of the LinkedList, and lists them in order.  */
	virtual std::string toString() const = 0;

	

protected:
	int m_count;

};




class ArrayBasedList : public IList
{
public:
	ArrayBasedList();
	/** Adds a value to the LinkedList.  Adds the value to the end of the List. Return true if able to, otherwise false */
	bool add(int val) override;
	/** Remove a value to the LinkedList.  Return true if able to, otherwise false.
	Will only remove one entry if there are multiple entries with the same value */
	bool remove(int val) override;
	/** Remove  all elements from LinkedList */
	void clear() override;
	virtual ~ArrayBasedList() ;
	/** Generates a string of the contents of the LinkedList, and lists them in order.  */
	std::string toString() const override;
private:
	int m_values[10];

};

class PointerBasedLinkedList : public IList
{
public:
	PointerBasedLinkedList();
	/** Adds a value to the LinkedList. Adds the value to the end of the List. Return true if able to, otherwise false */
	bool add(int val) override;
	/** Remove a value to the LinkedList.  Return true if able to, otherwise false.
	Will only remove one entry if there are multiple entries with the same value */
	bool remove(int val)  override;
	/** Remove  all elements from LinkedList */
	void clear()  override;
	virtual ~PointerBasedLinkedList();
	/** Generates a string of the contents of the LinkedList, and lists them in order.  */
	std::string toString() const override;
private:
	Node * m_head;
	Node * m_tail;// this is optional to use, but it does make things easier
};



