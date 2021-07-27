
#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"
//#include "Nodes.hpp"
#include "Board.h"
//#include "mainGame.h"
using namespace std;

#define _CRTDBG_MAP_ALLOC
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//static void framebuffer_size_callback(GLFWwindow*, int, int);
//static void mouse_callback(GLFWwindow*, double, double);

/// Start!
/// stress testing the Node class implementation
struct Test
{
	short num;
	Test(short inNum) :num(inNum) {};
	friend ostream& operator<<(ostream& cout, const Test& data) { cout << data.num << ';'; return cout; }
};
void ListTest()
{
	typedef Node<Test> Node; // Nice shorthand to use
	typedef Nodeptr<Test> Test;
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
	Data(short inDest, short inDist) :Destination(inDest), Distance(inDist) {};
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
			Node<Data>::insertLeft(&List[city1], new Nodeptr<Data>(Data(city2, dist)));
			Node<Data>::insertLeft(&List[city2], new Nodeptr<Data>(Data(city1, dist)));
		}
		fin.close();
	}
	else
		cout << "Error opening file: " << file << endl;
}

/// Test loop for functionality!
void test()
{
	//ListTest();

	//Node<Data> List[20];
	//readInput(&List[0]);
	//for (int ii = 0; ii < 20; ii++)
	//{
	//	cout << endl << "List " << ii << ": ";
	//	for (int xx = 0; xx < Node<Data>::getSize(&List[ii]); xx++)
	//		cout << Node<Data>::getData(&List[ii], xx);
	//}
	// 
	DFSBoard sample1;
	BFSBoard sample2;
	IDSBoard sample3;
	short count[3] = { 0 };
	while (sample1.isDone() == false || sample2.isDone() == false || sample3.isDone() == false)
	{
		if (sample1.isDone() == false)
		{
			count[0]++;
			cout << endl << "DFS";sample1.update();
		}
		if (sample2.isDone() == false)
		{
			count[1]++;
			cout << endl << "BFS"; sample2.update();
		}
		if (sample3.isDone() == false)
		{
			count[2]++;
			cout << endl << "IDS"; sample3.update();
		}
	}
	cout << endl << "DFS" << endl << "Count: " << count[0]; sample1.draw();
	cout << endl << "BFS" << endl << "Count: " << count[1]; sample2.draw();
	cout << endl << "IDS" << endl << "Count: " << count[2]; sample3.draw();
}
/// From start to can be deleted. All for testing!

bool complete(DFSBoard d, BFSBoard b, IDSBoard i) {
	return d.isDone() && b.isDone() && i.isDone();
}
void mainRun() {
	int choice;
	for (int i = 0; i < 20; ++i)
		cout << CityDat(i, 0) << "\t: " << i << std::endl;
	cout << "From the above, select a starting city by number: ";
	cin >> choice;
	DFSBoard dfs = DFSBoard(short(choice), short(0));
	BFSBoard bfs = BFSBoard(short(choice), short(0));
	IDSBoard ids = IDSBoard(short(choice), short(0));
	while (!complete(dfs, bfs, ids)) {
		if (!dfs.isDone()) dfs.update();
		if (!bfs.isDone()) bfs.update();
		if (!ids.isDone()) ids.update();
	}
	cout << "DFS FINAL:" << endl;
	dfs.draw();
	cout << "BFS FINAL:" << endl;
	bfs.draw();
	cout << "IDS FINAL:" << endl;
	ids.draw();
}
int main()
{
	mainRun();
}
