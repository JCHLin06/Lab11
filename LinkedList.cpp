// LinkedList.cpp : Defines the exported functions for the DLL application.
//

#include "LinkedList.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

IList::IList() : m_count(0)
{

}


int IList::getSize() const
{
	return m_count;
}

/** Returns true  if list is empty, otherwise true */
bool IList::isEmpty() const
{
	// if m_count is 0, then the list is empty
	if (m_count == 0) {
		return true;
	}
	// otherwise the list is not empty (as m_count is not 0)
	return false;
}

PointerBasedLinkedList::PointerBasedLinkedList() : IList(), m_head(nullptr), m_tail(nullptr){}

/** Adds a value to the LinkedList.  Return true if able to, otherwise false */
bool PointerBasedLinkedList::add(int val)
{
	// currently the list is empty, we need to modify m_head and m_tail to make
	// a list of a single element
	if (m_head == nullptr) {
		m_head = new Node(val);
		m_tail = m_head;
	} else {
		// adding an element to the end of the list
		m_tail->setNext(new Node(val)); // setting the next value of the previous tail
		m_tail = m_tail->getNext(); // making the tail to the new tail
	}
	m_count++; // housekeeping to increase length count
	return true;
}

/** Remove a value to the LinkedList.  Return true if able to, otherwise false.
Will only remove one entry if there are multiple entries with the same value */
bool PointerBasedLinkedList::remove(int val)
{
	// previous is the previous value in the list
	// current is the current value in the list at iteration
	Node* previous = nullptr;
	Node* current = m_head;
	// looping through the list
	while (current != nullptr && current->getItem() != val) {
		previous = current;
		current = current->getNext();
	}
	if (current != nullptr && previous != nullptr) {
		// if current and previous are not nullptrs, we have found the value
		// somewhere in the list
		Node* next = current->getNext();
		// if next is null, then the value we found is the tail
		if (next != nullptr) {
			// the value is somewhere in the middle of the list
			previous->setNext(current->getNext()); // linking previous to the skip
			current->setNext(nullptr); // delinking current to make it safe to delete
			delete current; // delete the value we are removing (cleaning up memory)
			m_count--; // housekeeping
			return true;
		} else {
			// the value is the tail of the list
			previous->setNext(nullptr); // setting previous as tail (depicted with a next = nullptr)
			delete current; // delete the value we are removing (cleaning up memory) no need to delink since next == nullptr
			m_count--; // housekeeping
			m_tail = previous; // housekeeping of the tail of the list
			return true;
		}
	} else if (current != nullptr) {
		// previous == nullptr here
		// meaning we found the value at the head of the list
		// temporarily hold the next value
		Node* tmp = current->getNext();
		current->setNext(nullptr); // delink the current value to make it safe to delete
		delete current; // delete the value we are removing (cleaning up memory)
		m_head = tmp; // housekeeping of the head of the list
		m_count--; // housekeeping
		return true;
	} else {
		// we did not find any instance of `val` in the list
		return false;
	}
}

/** Remove  all elements from LinkedList */
void PointerBasedLinkedList::clear()
{
	// if the list already isn't empty
	if (m_head != nullptr) {
		// delete the head node (allow node destructor ~Node to clean up the rest of the list)
		delete m_head;
		m_head = nullptr; // housekeeping
		m_tail = nullptr; // housekeeping
		m_count = 0; // housekeeping
	}
}
PointerBasedLinkedList::~PointerBasedLinkedList()
{
	clear();
}

std::string PointerBasedLinkedList::toString() const
{
	string str = "";
	Node* current = m_head;
	// looping through all nodes in the list
	while (current != nullptr) {
		str += std::to_string(current->getItem());
		// if the value isn't the tail, add a space
		if (current != m_tail) {
			str += " ";
		}
		current = current->getNext();
	}
	return str;
}

ArrayBasedList::ArrayBasedList() : IList()
{
    m_count = 0;
	// you got it for free :)
}

bool ArrayBasedList::add(int val)
{
	// since the m_values array has a size of 10, if we add when the list is full, we fail
	if (m_count == 10) {
		return false;
	}

	m_values[m_count] = val; // setting the value
	m_count++; // housekeeping
	return true;
}
bool ArrayBasedList::remove(int val)
{
	bool found = false; // holder for finding the first instance of the value
	int tmp[10]; // temporary array to hold all non first instance of val
	int j = 0; // counter for the tmp array
	for (int i = 0; i < m_count; i++) {
		// if the current value does not equal val or if the val has already been found
		// add that value to the tmp array to copy over
		if (m_values[i] != val || (found == true)) {
			tmp[j] = m_values[i];
			j++;
		} else {
			// marking as found of first instance of val
			found = true;
		}
	}
	// if the val was found
	// copy over all values in the temporary array into the m_values array
	if (found == true) {
		for (int i = 0; i < m_count - 1; i++) {
			m_values[i] = tmp[i];
		}
		m_count--; // housekeeping
	}
	// if the value was found, then the remove would be successful, otherwise it wouldn't be successful
	return found;
}
void ArrayBasedList::clear()
{
	// set length to 0, the rest of the array will be overridden when re-adding values
	m_count = 0;
}
ArrayBasedList::~ArrayBasedList()
{
	clear();
}

std::string ArrayBasedList::toString() const
{
	string str = "";
	// looping over all elements in the list to add to the string
	for (int i = 0; i < m_count; i++) {
		str += std::to_string(m_values[i]);
		if (i != m_count-1) {
			str.push_back(' ');
		}
	}
	return str;
}