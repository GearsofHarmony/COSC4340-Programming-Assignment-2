#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H


const float PI = 3.1415926f;
const int WIDTH = 800;
const int HEIGHT = 600;

enum City 
{ 
	Bucharest, Oradea, Zerind, Arad, 
	Timisoara, Lugoj, Mehadia, Drobeta, 
	Craiova, Rimnieu_Vilcea, Sibiu, Fagaras,
	Pitesti, Giurgiu, Urziceni, Hirsova, 
	Eforie, Vaslui, Iasi, Neamt 
};

template<typename T> void FREE(T*& ptr) { if (ptr) { delete(ptr); (ptr) = 0; } };
template<typename T> void FREE_ARRAY(T*& ptr) { if (ptr) { delete[](ptr); (ptr) = 0; } };
#endif // !CONSTANTS_H
