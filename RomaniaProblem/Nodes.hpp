#pragma once
#ifndef NODES_HPP
#define NODES_HPP
#include "constants.h"

/**
 * Circular Linked list data storage and data retrieval
 * which can be expanded as an array of circular linked lists.
 * 
 * @tparam Nodeptr is the data type to be stored
 *     @note The user MUST implement a pointer variable named "next" that 
 *         points to it's own data type for this data structure to 
 *         work properly. For Example:
 *             struct foo
 *		       {
 *                 int randomData;
 *                 foo* next;
 *             }
 * @param size is the list size where if 0 the list is empty.
 * @param head is a pointer to the beginning of the list.
 */
template<typename Nodeptr>
class Node
{
private:
	int size;
	Nodeptr* head;
public:
	/**
	* @param size, head will be initialized to 0
	*/
	Node() { size = 0; head = NULL; };
	/**
	* Upon deletion check list if empty, if false then delete each entry of list
	*/
	~Node()
	{
		if (this->size != 0)
			deleteList(this);
	};
	/**
	* @param[in] 'list' is the referenced list used.
	*     'list' is made constant to prevent modification of values.
	* @returns 'list->size' is the returning value of type 'int'
	* @throw no throw exceptions are made
	*/
	static int getSize(const Node* list) { return list->size; }
	/**
	* @param[in] 'list' is the referenced list.
	* @param[in] 'index' is the indexed entry to search.
	* @returns 'ptr' is returned once found check @tparam
	* @throw basic an exception is thrown when 'index' > 'list->size' is true
	*     The function will continue regardless due to the list being circular
	*/
	static Nodeptr getData(const Node* list, int index)
	{
		Nodeptr* ptr;
		ptr = list->head;

		if (index > list->size)
			std::cout << "Index exceeds list size!";

		for (int ii = 0; ii < index; ii++)
		{
			ptr = ptr->next;
		}
		return *ptr;
	}
	/**
	* Insert new entry to the left or beginning of the list.
	* @param[in out] 'list' is the referenced list
	* @param[in] 'item' is the new entry to be added
	* @throw none no exceptions are made 
	* @warning Must be done correctly when calling this method see note below for proper call
	* @note the best way to create a new entry is to:
	*     Node<Data>::insertLeft(&List[index], new Data(param1, param2));
	* This is to assume that the user has created an explicit constructor for the new data entry.
	*/
	static void insertLeft(Node* list, Nodeptr* item)
	{
		Nodeptr* ptr;
		ptr = item;
		if (list->head == NULL)
		{
			ptr->next = ptr;
			list->head = ptr;
		}
		else
		{
			ptr->next = list->head;
			list->head = ptr;
			for (int ii = 0; ii < list->size; ii++)
			{
				ptr = ptr->next;
			}
			ptr->next = list->head;
		}
		list->size += 1;
	};
	/**
	* Insert new entry to the right or end of the list.
	* @param[in out] 'list' is the referenced list
	* @param[in] 'item' is the new entry to be added
	* @throw none no exceptions are made 
	* @warning Must be done correctly when calling this method see note below for proper call
	* @note the best way to create a new entry is to:
	*     Node<Data>::insertRight(&List[index], new Data(param1, param2));
	* This is to assume that the user has created an explicit constructor for the new data entry.
	*/
	static void insertRight(Node* list, Nodeptr* item)
	{
		insertLeft(list, item);
		list->head = list->head->next;
	};
	/**
	* Delete entry from beginning of list
	* @param[in out] 'list' is the referenced list
	* @throw basic when the 'list->head' is null then an underflow is detected and the function ceases
	*/
	static void deleteLeft(Node* list)
	{
		Nodeptr* ptr;
		ptr = list->head;
		if (ptr == NULL)
		{
			std::cout << "\nUnderflow detected!" << std::endl;
		}
		else
		{

			list->head = ptr->next;
			for (int ii = 1; ii < list->size; ii++)
			{
				ptr = ptr->next;
			}
			FREE(ptr->next);
			ptr->next = list->head;
			if (list->size == 1)
			{
				list->head = NULL;
			}
			list->size -= 1;
		}
	};
	/**
	* Delete entry from end of list
	* @param[in out] 'list' is the referenced list
	* @throw basic when the 'list->head' is null then an underflow is detected and the function ceases
	*/
	static void deleteRight(Node* list)
	{
		Nodeptr* ptr;
		ptr = list->head;
		if (ptr == NULL)
		{
			std::cout << "\nUnderflow detected!" << std::endl;
		}
		else
		{
			for (int ii = 2; ii < list->size; ii++)
			{
				ptr = ptr->next;
			}
			FREE(ptr->next);
			ptr->next = list->head;
			if (list->size == 1)
			{
				list->head = NULL;
			}
			list->size -= 1;
		}
	};
	/**
	* Delete entire list
	* @param[in out] 'list' is the referenced list
	* @throw basic when the 'list->head' is null then an underflow is detected and the function ceases
	*/
	static void deleteList(Node* list)
	{
		Nodeptr* ptr;
		ptr = list->head;
		if (ptr == NULL)
		{
			std::cout << "\nUnderflow detected!" << std::endl;
		}
		else
		{
			for (int ii = 0; ii < list->size; ii++)
			{
				list->head = ptr->next;
				FREE(ptr);
				ptr = list->head;
			}
			list->size = 0;
			list->head = NULL;
		}
	};
	/**
	* Print contents of list
	* @param[in out] 'list' is the referenced list
	* @throw none
	* @note It is strongly recommended that the user creates their own
	*     instance of cout through ostream& operator<<(ostream& cout, Data& data) 
	*     where 'Data' is the data type used for tparam Nodeptr
	*/
	static void printList(Node* list)
	{
		Nodeptr* ptr;
		ptr = list->head;
		for (int ii = 0; ii < list->size; ii++)
		{
			std::cout << *ptr;
			ptr = ptr->next;
		}
	};
};
#endif