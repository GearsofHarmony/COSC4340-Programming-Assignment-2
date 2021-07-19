#include "Nodes.h"
#include <iostream>

Node::Node() { size = 0; head = 0; };
Node::~Node()
{
	if (this->size != 0)
		deleteList(this);
};
void Node::insertLeft(Node* list, Nodeptr* item)
{
	Nodeptr* ptr;
	ptr = item;
	if (list->head == 0)
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
}
void Node::insertRight(Node* list, Nodeptr* item)
{
	insertLeft(list, item);
	list->head = list->head->next;
}
void Node::deleteLeft(Node* list)
{
	Nodeptr* ptr;
	ptr = list->head;
	if (ptr == 0)
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
			list->head = 0;
		}
		list->size -= 1;
	}
}
void Node::deleteRight(Node* list)
{
	Nodeptr* ptr;
	ptr = list->head;
	if (ptr == 0)
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
			list->head = 0;
		}
		list->size -= 1;
	}
}
void Node::deleteList(Node* list)
{
	Nodeptr* ptr;
	ptr = list->head;
	if (ptr == 0)
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
		list->head = 0;
	}
}
void Node::printList(Node* list)
{
	Nodeptr* ptr;
	ptr = list->head;
	for (int ii = 0; ii < list->size; ii++)
	{
		ptr->print();
		ptr = ptr->next;
	}
}