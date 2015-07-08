//--------------------------------------------------------------------
//
//  Laboratory 5                                          ListLinked.h
//
//  Class declaration for the linked implementation of the List ADT
//
//--------------------------------------------------------------------

#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename DataType>
class ListNode;

template <typename DataType>
class List {
public:
	List(int = 0); //Default constructor, creates an empty list.
    List(const List<DataType>&); //Copy constructor, creates an empty list then calls assignment.
    List<DataType>& operator=(const List<DataType>&); //Assignment operator, calls overloaded equality to avoid self-assignment.
    ~List(); //Destructor, calls remove recursively.
	void insert(const DataType&);//Creates a new node after the cursor position.
	//Requires: A valid object of type DataType.
	//Result: A new node inserted after the cursor.
    void remove(); //Deletes the cursor node, moving the cursor to the next node.
	//Requires: A non-empty list.
	//Result: The current node is deleted, cursor points to the next node (or the head if the deleted node was at the end).
    void replace(const DataType&);
    void clear();
    bool isEmpty() const; // returns true if head is null, false if head is not null
    bool isFull() const;
    void gotoBeginning();
    void gotoEnd();
    bool gotoNext();
    bool gotoPrior();
    DataType getCursor() const;
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
		}
		else
		{
			head = cursor->next;
			delete cursor;
		}
	}
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
