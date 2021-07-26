#pragma once
#include "Board.h"
#include "math.h"
#include "constants.h"
class GraphicalInterface
{
public:
	GraphicalInterface();
	void draw();
	void update();
	void init();
	void run();
	bool initializing = true;
private:
	SelectionBoard sb;
	DFSBoard dfs;
	BFSBoard bfs;
	IDSBoard ids;
	bool isMore();
};

