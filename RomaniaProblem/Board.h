#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <fstream>
#include "Nodes.hpp"
//#include "Stacks.hpp"
using namespace std;

const int MSIZE = 20;
struct CityDat
{
	short Destination;
	short Distance;
	//CityDat* next;
	explicit CityDat(short inDest = 0, short inDist = 0) :Destination(inDest), Distance(inDist) {};
	friend std::ostream& operator<<(std::ostream& cout, const CityDat& data) 
	{ 
		switch (data.Destination)
		{
		case 0: cout << "A-Bucharest, "; break;
		case 1: cout << "B-Oradea, "; break;
		case 2: cout << "C-Zerind, "; break;
		case 3: cout << "D-Arad, "; break;
		case 4: cout << "E-Timisoara, "; break;
		case 5: cout << "Lugoj, "; break;
		case 6: cout << "Mehadia, "; break;
		case 7: cout << "Drobeta, "; break;
		case 8: cout << "Craiova, "; break;
		case 9: cout << "Rimnieu_Vilcea, "; break;
		case 10: cout << "Sibiu, "; break;
		case 11: cout << "Fagaras, "; break;
		case 12: cout << "Pitesti, "; break;
		case 13: cout << "Giurgiu, "; break;
		case 14: cout << "Urziceni, "; break;
		case 15: cout << "Hirsova, "; break;
		case 16: cout << "Eforie, "; break;
		case 17: cout << "Vaslui, "; break;
		case 18: cout << "Iasi, ";break;
		case 19: cout << "Neamt, ";break;
		}
		return cout; 
	}
};

class BaseBoard
{
public:
	Node<CityDat> Map[MSIZE];
	short startNode;
	short endNode;

	BaseBoard();
	~BaseBoard();
	virtual void draw();
	virtual void update();
};

class SelectionBoard
{

};

class DFSBoard : BaseBoard
{
public:
	Node<CityDat> DFSMap[MSIZE];
	Node<CityDat> path;
	bool done;

	DFSBoard();
	void draw();
	void update();
};

class BFSBoard : BaseBoard
{
public:
	Node<CityDat> BFSMap[MSIZE];
	Node<CityDat> toVisit;
	Node<CityDat> path;
	bool done;

	BFSBoard();
	void draw();
	void update();
};

class IDSBoard : BaseBoard
{
public:
	Node<CityDat> toVisit[MSIZE];
	Node<CityDat> path;
	bool done;

	IDSBoard();
	void draw();
	void update();
};
#endif