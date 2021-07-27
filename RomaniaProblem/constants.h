#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MSIZE = 20;
// List of cities
enum City 
{ 
	Bucharest, Oradea, Zerind, Arad, 
	Timisoara, Lugoj, Mehadia, Drobeta, 
	Craiova, Rimnieu_Vilcea, Sibiu, Fagaras,
	Pitesti, Giurgiu, Urziceni, Hirsova, 
	Eforie, Vaslui, Iasi, Neamt 
};
/// Safe delete pointer in heap
template<typename T> void FREE(T*& ptr) { if (ptr) { delete(ptr); (ptr) = NULL; } };
/// Safe delete pointer array in heap
template<typename T> void FREE_ARRAY(T*& ptr) { if (ptr) { delete[](ptr); (ptr) = NULL; } };
#endif // !CONSTANTS_H
