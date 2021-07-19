#pragma once
#ifndef NODES_H
#define NODES_H
#include <iostream>
#include "constants.h"

struct Nodeptr
{
	Nodeptr* next = 0;
	virtual void print() = 0;
};

class Node
{
private:
	int size;
	Nodeptr* head;
public:
	Node();
	~Node();

	int getSize(Node* list) { return list->size; }
	static Nodeptr* getFirst(Node* list) { return list->head; }
	static Nodeptr* getNext(Nodeptr* item) { return item->next; }

	static void insertLeft(Node* list, Nodeptr* item);
	static void insertRight(Node* list, Nodeptr* item);
	static void deleteLeft(Node* list);
	static void deleteRight(Node* list);
	static void deleteList(Node* list);
	static void printList(Node* list);
};
#endif