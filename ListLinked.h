/*--------------------------------------------------------------------*\

CSC2200 - Laboratory 5 - 07/15/2015             ListLinked.h

Class declaration for the linked implementation of the List ADT

System Architect: Benjamin Ciaglo
Data Architect: Mark Stiles
Developer: Anthony Mauro

\*--------------------------------------------------------------------*/

/**********************************************************************\
Dates compiled and results:
07/09/15:
- This is an Example...Please change accordingly.
- Tested gotoBeginning. Function worked fine.
- Tested isFull. Function failed to compile.

\**********************************************************************/

// Header //
#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

// Classes //
template <typename DataType>
class ListNode;

template <typename DataType>
class List {
public:
	List(int = 0); //Default constructor, creates an empty list.
	List(const List<DataType>&); //Copy constructor, creates an empty list then calls assignment.
	List<DataType>& operator=(const List<DataType>&); //Assignment operator, calls overloaded equality to avoid self-assignment.
	~List(); //Destructor, calls clear.
	void insert(const DataType&);//Creates a new node after the cursor position.
	//Requires: A valid object of type DataType.
	//Result: A new node inserted after the cursor.
	void remove(); //Deletes the cursor node, moving the cursor to the next node.
	//Requires: A non-empty list.
	//Result: The current node is deleted, cursor points to the next node (or the head if the deleted node was at the end).
	void replace(const DataType&); //Replaces the data at the cursor with the parameter.
	//Requires: A non-empty list, a DataType.
	//Result: The value at the cursor is set to the input.
	void clear(); //Uses a loop to remove every node.
	//Requires: A non-empty list.
	//Result: An empty list.
	bool isEmpty() const; // returns true if head is null, false if head is not null
	bool isFull() const; // returns true if head is not null, false if the head is null
	void gotoBeginning(); // sets curser at beginning of the list
	void gotoEnd(); // sets curser at the end of the list
	bool gotoNext(); // moves curser to the next item in the list
	bool gotoPrior(); // moves curser to the previous item in the list
	DataType getCursor() const; // returns the value stored at curser
	bool operator==(const List<DataType>&) const; //Equality operator, calls equalityHelper to check every node in both trees.
	//Requires: Another List of the same DataType.
	//Result: Returns the equality of the two Lists.
	ListNode<DataType>* assignHelper(ListNode<DataType>*&, const ListNode<DataType>*); //Recursive helper for assignment operator.
	//Requires: A NULL pointer and a pointer to a valid node.
	//Result: Recursively creates the new list.
	bool equalityHelper(const ListNode<DataType>*, const ListNode<DataType>*) const; //Recursive helper for equality operator.
	//Requires: Two node pointers.
	//Result: Recursively returns the equality of the nodes and their children.

	// Programming exercise 2
	// void moveToBeginning () throw (logic_error);

	// Programming exercise 3
	// void insertBefore(const DataType& newDataItem) throw (logic_error);

	void showStructure() const;

private:

	ListNode<DataType>* head;
	ListNode<DataType>* cursor;

};

template <typename DataType>
class ListNode {
	template <typename DataType>
	friend class List;
public:
	ListNode(const DataType&, ListNode<DataType>* = NULL);
	DataType dataItem;
	ListNode<DataType>* next;
};


// Function Definitions //
template <typename DataType>
List<DataType>::List(int ignored = 0)
{
	head = NULL;
	cursor = NULL;
}

template <typename DataType>
List<DataType>::List(const List<DataType>& other)
{
	head = NULL;
	cursor = NULL;
	this = other;
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List<DataType>& other)
{
	if (!(this == other))
	{
		clear();
		head = assignHelper(head, other.head);
		cursor = head;
	}
	return this;
}

template <typename DataType>
List<DataType>::~List()
{
	clear();
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem)
{
	if (isEmpty())
	{
		head = new ListNode<DataType>(newDataItem);
		cursor = head;
	}
	else
	{
		cursor->next = new ListNode<DataType>(newDataItem, cursor->next);
		cursor = cursor->next;
	}
	return;
}

template <typename DataType>
void List<DataType>::remove()
{
	if (NULL != cursor)
	{
		ListNode<DataType>* temp = cursor->next;
		if (gotoPrior())
		{
			delete cursor->next;
			cursor->next = temp;
			if (gotoNext());
			else
				gotoBeginning();
		}
		else
		{
			if (temp)
			{
				head = temp;
				delete cursor;
				cursor = head;
			}
			else
			{
				delete head;
				head = NULL;
				cursor = NULL;
			}
		}
	}
	return;
}

template <typename DataType>
void List<DataType>::replace(const DataType& input)
{
	cursor->dataItem = input;
	return;
}

template <typename DataType>
void List<DataType>::clear()
{
	while (NULL != head)
		remove();
	return;
}

template <typename DataType>
bool List<DataType>::isEmpty() const
{
	if (head == NULL)
		return true;
	else
		return false;
}

template <typename DataType>
bool List<DataType>::isFull() const
{
	return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning()
{
	cursor = head;
	return;
}

template <typename DataType>
void List<DataType>::gotoEnd()
{
	if (cursor->next == NULL)
		return;
	cursor = cursor->next;
	gotoEnd();
}

template <typename DataType>
bool List<DataType>::gotoNext()
{
	if (cursor->next)
	{
		cursor = cursor->next;
		return 1;
	}
	else
		return 0;
}

template <typename DataType>
bool List<DataType>::gotoPrior()
{
	if (cursor == head)
		return 0;
	ListNode<DataType>* temp = head;
	while (temp != NULL && temp != cursor)
	{
		if (temp->next == cursor)
		{
			cursor = temp;
			return 1;
		}
		temp = temp->next;
	}
	return 1;
}

template <typename DataType>
DataType List<DataType>::getCursor() const
{
	return cursor->dataItem;
}

template<typename DataType>
bool List<DataType>::operator==(const List<DataType>& other) const
{
	return equalityHelper(head, other.head);
}

template <typename DataType>
ListNode<DataType>* List<DataType>::assignHelper(ListNode<DataType>*& here, const ListNode<DataType>* other)
{
	here = new ListNode<DataType>(other->dataItem);
	here->next = NULL;
	if (NULL != other->next)
		here->next = assignHelper(here->next, other->next);
	return here;
}

template <typename DataType>
bool List<DataType>::equalityHelper(const ListNode<DataType>* here, const ListNode<DataType>* other) const
{
	if (here->dataItem != other->dataItem)
		return 0;
	else if ((NULL == here->next) && (NULL != other->next))
		return 0;
	else if ((NULL != here->next) && (NULL == other->next))
		return 0;
	else
		return equalityHelper(here->next, other->next);
}

template <typename DataType>
ListNode<DataType>::ListNode(const DataType& nodeData, ListNode<DataType>* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}
