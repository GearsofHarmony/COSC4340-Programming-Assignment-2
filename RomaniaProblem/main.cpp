//#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "constants.h"
#include "Nodes.hpp"
//#include "mainGame.h"
using namespace std;

#define _CRTDBG_MAP_ALLOC
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

static void framebuffer_size_callback(GLFWwindow*, int, int);
//static void mouse_callback(GLFWwindow*, double, double);

struct Test
{
	short num;
	Test* next;
	explicit Test(short inNum) :num(inNum) { next = NULL; };
	friend ostream& operator<<(ostream& cout, const Test& data) { cout << data.num << ';'; return cout; }
};
/// stress testing the Node class implementation
void ListTest()
{
	typedef Node<Test> Node; // Nice shorthand to use
	Node* list = new Node[4];
	//Node list[4];
	cout << endl << "Insert into List 0: L1";
	Node::insertLeft(&list[0], new Test(1));
	cout << endl << "Insert into List 0: L2";
	Node::insertLeft(&list[0], new Test(2));
	cout << endl << "Insert into List 0: L3";
	Node::insertLeft(&list[0], new Test(3));

	cout << endl << "Insert into List 1: R1";
	Node::insertRight(&list[1], new Test(1));
	cout << endl << "Insert into List 1: R2";
	Node::insertRight(&list[1], new Test(2));
	cout << endl << "Insert into List 1: R3";
	Node::insertRight(&list[1], new Test(3));

	cout << endl << "Insert into List 2: L1";
	Node::insertLeft(&list[2], new Test(1));
	cout << endl << "Insert into List 1: R2";
	Node::insertRight(&list[2], new Test(2));
	cout << endl << "Insert into List 1: L3";
	Node::insertLeft(&list[2], new Test(3));

	cout << endl << "Insert into List 3: L1";
	Node::insertLeft(&list[3], new Test(1));
	cout << endl << "Insert into List 3: L2";
	Node::insertLeft(&list[3], new Test(2));
	cout << endl << "Insert into List 3: R3";
	Node::insertRight(&list[3], new Test(3));

	for (int ii = 0; ii < 4; ii++)
	{
		cout << endl << "List " << ii << ": ";
		Node::printList(&list[ii]);
	}

	cout << endl << "Delete from List 0: L";
	Node::deleteLeft(&list[0]);
	cout << endl << "Delete from List 0: L";
	Node::deleteLeft(&list[0]);
	cout << endl << "Delete from List 0: L";
	Node::deleteLeft(&list[0]);
	cout << endl << "Delete from List 0: L";
	Node::deleteLeft(&list[0]);
	cout << endl << "Delete from List 1: R";
	Node::deleteRight(&list[1]);
	cout << endl << "Delete List 2:";
	Node::deleteList(&list[2]);
	cout << endl << "Delete from List 3: R";
	Node::deleteRight(&list[3]);
	cout << endl << "Delete from List 3: R";
	Node::deleteRight(&list[3]);
	cout << endl << "Delete from List 3: R";
	Node::deleteRight(&list[3]);
	cout << endl << "Delete from List 3: R";
	Node::deleteRight(&list[3]);
	cout << endl;

	for (int ii = 0; ii < 4; ii++)
	{
		cout << endl << "List " << ii << ": ";
		Node::printList(&list[ii]);
	}
	FREE_ARRAY(list);
	cout << endl;
}
/// Data Structure for map information
struct Data
{
	short Destination;
	short Distance;
	Data* next;
	explicit Data(short inDest, short inDist) :Destination(inDest), Distance(inDist) { next = NULL; };
	friend ostream& operator<<(ostream& cout, const Data& data) { cout << data.Destination << ',' << data.Distance << ';'; return cout; }
};

/**
 * Read from file "input.txt" and builds Romania map
 * @param 'List' is a pointer to the referenced list strongly recommend typing "&List[index]
 * @throw basic if the file fails to open then a message is displayed and the function passes without conducting primary task.
 */
void readInput(Node<Data>* List)
{
	char file[] = { "input.txt" };
	int city1, city2, dist;
	fstream fin(file, ios::in);
	if (fin.is_open())
	{
		while (fin.eof() == false)
		{
			fin >> city1 >> city2 >> dist;
			Node<Data>::insertLeft(&List[city1], new Data(city2, dist));
			Node<Data>::insertLeft(&List[city2], new Data(city1, dist));
		}
		fin.close();
	}
	else
		cout << "Error opening file: " << file << endl;
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "COSC4340 AI", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 100, 100);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	ListTest();
	//typedef Node<Data> Node;
	Node<Data> List[20];
	readInput(&List[0]); 
	for (int ii = 0; ii < 20; ii++)
	{
		cout << endl << "List " << ii << ": ";
		for (int xx = 0; xx < Node<Data>::getSize(&List[ii]); xx++)
			cout << Node<Data>::getData(&List[ii], xx);
	}

	//MainGame* game = new MainGame();
	//game->initialize(window);
	while (!glfwWindowShouldClose(window))
	{
		//game->run(window);	//main loop of program
		// Input
		// -----
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		// Render
		// ------
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//delete game;
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//void mouse_callback(GLFWwindow* window, double xPos, double yPos){}