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
    void remove();
    void replace(const DataType&);
    void clear();
    bool isEmpty() const;
    bool isFull() const;
    void gotoBeginning();
    void gotoEnd() throw;
    bool gotoNext() throw;
    bool gotoPrior() throw;
    DataType getCursor() const;
	bool operator==(const List<DataType>&) const;
	ListNode<DataType>* assignHelper(ListNode<DataType>*&, const ListNode<DataType>*); //Recursive helper for assignment operator.
	//Requires: A NULL pointer and a pointer to a valid node.
	//Result: Recursively creates the new list.

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
ListNode<DataType>* List<DataType>::assignHelper(ListNode<DataType>*& here, const ListNode<DataType>* other)
{
	here = new ListNode<DataType>(other->dataItem);
	here->next = NULL;
	if (NULL != other->next)
		here->next = assignHelper(here->next, other->next);
	return here;
}

template <typename DataType>
ListNode<DataType>::ListNode(const DataType& nodeData, ListNode<DataType>* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}
