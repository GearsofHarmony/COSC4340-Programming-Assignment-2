#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Board.h"
#include "math.h"
#include "constants.h"
class GraphicalInterface
{
public:
	GraphicalInterface();
	void draw(GLFWwindow*);
	void update();
	void init();
	void run(GLFWwindow*);
	bool initializing = true;
private:
	SelectionBoard sb;
	DFSBoard dfs;
	BFSBoard bfs;
	IDSBoard ids;
	bool isMore();
};

