#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <fstream>
#include "constants.h"
#include "Nodes.hpp"
//#include "Stacks.hpp"
using namespace std;

/**
 * CityDat is the data of each location and the distance to travel to reach destination
 */
struct CityDat
{
	short Destination;
	short Distance;
	explicit CityDat(short inDest = 0, short inDist = 0) :Destination(inDest), Distance(inDist) {};
	friend std::ostream& operator<<(std::ostream& cout, const CityDat& data) 
	{ 
		switch (data.Destination)
		{
		case 0: cout << "Bucharest, "; break;
		case 1: cout << "Oradea, "; break;
		case 2: cout << "Zerind, "; break;
		case 3: cout << "Arad, "; break;
		case 4: cout << "Timisoara, "; break;
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
/**
 * Class BaseBoard is the base template for gui interface and base information for all search algorithms
 * @param Map is the base map to build each search algorithm's map this is not and will not be modified
 * @param startNode is the starting location the user chooses
 * @param endNode is the destination location the algorithm searches for.
 */
class BaseBoard
{

public:
	Node<CityDat> Map[MSIZE];
	short startNode;
	short endNode;

	/**
	* This constructor reads from a file that contains the map data and builds the map
	*/
	BaseBoard();
	BaseBoard(int, int);
	// Currently does nothing
	~BaseBoard();
	/**
	* Draws the map in terminal
	*/
	virtual void draw();
	// currently does nothing
	virtual void update();
};

class SelectionBoard
{

};
/**
* Depth First Search board that searches the map for the chosen destination
* @param DFSMap is used to check if a location is visited or not by deleting said location from list
* @param path is the final route taken to destination from origin
* @param done is checked if the DFS is done searching or not
*/
class DFSBoard : BaseBoard
{
protected:
	Node<CityDat> DFSMap[MSIZE];
	Node<CityDat> path;
	bool done;

public:
	DFSBoard();
	DFSBoard(int,int);
	/// @return if the search is done or not
	bool isDone() { return done; }
	/**
	* Draws the map in terminal
	*/
	void draw();
	/**
	* Main loop of search algorithm by one iteration
	*/
	void update();
};
/**
* Breadth First Search board that searches the map for the chosen destination
* @param BFSMap is used to check if a location is visited or not by deleting said location from list
* @param toVisit is a place holder for locations to visit before proceeding to the next breadth iteration
* @param path is the final route taken to destination from origin
* @param done is checked if the DFS is done searching or not
*/
class BFSBoard : BaseBoard
{
protected:
	Node<CityDat> BFSMap[MSIZE];
	Node<CityDat> toVisit;
	Node<CityDat> probePath[MSIZE];
	Node<CityDat> path;
	bool done;

public:
	BFSBoard();
	BFSBoard(int, int);
	/// @return if the search is done or not
	bool isDone() { return done; }
	/**
	* Draws the map in terminal
	*/
	void draw();
	/**
	* Main loop of search algorithm by one iteration
	*/
	void update();
};
/**
* Iterative Deepening Search board that searches the map for the chosen destination
* @param IDSMap is used to check if a location is visited or not by deleting said location from list
* @param path is the final route taken to destination from origin
* @param depthLimit is the limit must attempt to reach before iterating to the next level of the graph
* @param depth is the current depth iteration
* @param done is checked if the DFS is done searching or not
*/
class IDSBoard : BaseBoard
{
protected:
	Node<CityDat> IDSMap[MSIZE];
	Node<CityDat> path;
	int depthLimit;
	int depth;
	bool done;

public:
	IDSBoard();
	IDSBoard(int, int);
	/// @return if the search is done or not
	bool isDone() { return done; }
	/**
	* Draws the map in terminal
	*/
	void draw();
	/**
	* Main loop of search algorithm by one iteration
	*/
	void update();
};
#endif