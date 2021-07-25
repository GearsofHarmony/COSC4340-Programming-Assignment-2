#include "Board.h"

BaseBoard::BaseBoard()
{
	char file[] = { "input.txt" };
	int city1, city2, dist;
	fstream fin(file, ios::in);
	if (fin.is_open())
	{
		while (fin.eof() == false)
		{
			fin >> city1 >> city2 >> dist;
			Node<CityDat>::insertRight(&Map[city1], new Nodeptr<CityDat>(CityDat(city2, dist)));
			Node<CityDat>::insertRight(&Map[city2], new Nodeptr<CityDat>(CityDat(city1, dist)));
		}
		fin.close();
	}
	else
		cout << "Error opening file: " << file << endl;
	startNode = 0;
	endNode = 4;
}
BaseBoard::~BaseBoard() {}
void BaseBoard::draw()
{
	for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "List " << ii << ": ";
		Node<CityDat>::printList(&Map[ii]);
	}
}
void BaseBoard::update() {};

DFSBoard::DFSBoard()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	done = false;

	for (int ii = 0; ii < MSIZE; ii++) {
		for (int xx = 0; xx < Node::getSize(&Map[ii]); xx++) {
			if (startNode != Node::getData(&Map[ii], xx).Destination) {
				Node::insertRight(&DFSMap[ii], new Nodeptr(Node::getData(&Map[ii], xx)));
			}
		}
	}

	CityDat curNode(startNode, 0);
	Node::insertRight(&path, new Nodeptr(curNode));

	draw();
}
void DFSBoard::draw()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "List " << ii << ": ";
		Node::printList(&DFSMap[ii]);
	}
	cout << endl << "Path: ";
	Node::printList(&path);
	cout << endl;
}
void DFSBoard::update()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	CityDat curNode, probeNode;

	curNode = Node::getData(&path, Node::getSize(&path) - 1);
	if (curNode.Destination == endNode)
	{
		cout << "Goal Reached!";
		done = true;
		return;
	}
	if (Node::isEmpty(&DFSMap[curNode.Destination]) == false)
	{
		probeNode = Node::getData(&DFSMap[curNode.Destination], 0);
		Node::insertRight(&path, new Nodeptr(probeNode));
		Node::deleteLeft(&DFSMap[curNode.Destination]);

		for (int ii = 0; ii < MSIZE; ii++) {
			for (int xx = 0; xx < Node::getSize(&DFSMap[ii]); xx++) {
				if (probeNode.Destination == Node::getData(&DFSMap[ii], xx).Destination) {
					Node::deleteNode(&DFSMap[ii], xx);
				}
			}
		}
	}
	else
	{
		Node::deleteRight(&path);
	}

	draw();
}

BFSBoard::BFSBoard()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	done = false;

	for (int ii = 0; ii < MSIZE; ii++) {
		for (int xx = 0; xx < Node::getSize(&Map[ii]); xx++) {
			if (startNode != Node::getData(&Map[ii], xx).Destination) {
				Node::insertRight(&BFSMap[ii], new Nodeptr(Node::getData(&Map[ii], xx)));
			}
		}
	}

	CityDat curNode(startNode, 0);
	Node::insertRight(&toVisit, new Nodeptr(curNode));

	draw();
}
void BFSBoard::draw()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "List " << ii << ": ";
		Node::printList(&BFSMap[ii]);
	}
	cout << endl << "Path: ";
	Node::printList(&path);
	cout << endl << "To Visit: ";
	Node::printList(&toVisit);
	cout << endl;
}
void BFSBoard::update()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	CityDat curNode;

	if (Node::isEmpty(&toVisit) == false)
	{
		curNode = Node::getData(&toVisit, 0);
		Node::deleteLeft(&toVisit);
		Node::insertRight(&path, new Nodeptr(curNode));
	}
	else
	{
		curNode = Node::getData(&path, Node::getSize(&path) - 1);
	}

	if (curNode.Destination == endNode)
	{
		cout << "Goal Reached!";
		done = true;
		return;
	}
	if (Node::isEmpty(&BFSMap[curNode.Destination]) == false)
	{
		CityDat probeNode = Node::getData(&BFSMap[curNode.Destination], 0);
		Node::insertRight(&toVisit, new Nodeptr(probeNode));
		Node::deleteLeft(&BFSMap[curNode.Destination]);
		for (int ii = 0; ii < MSIZE; ii++) {
			for (int xx = 0; xx < Node::getSize(&BFSMap[ii]); xx++) {
				if (curNode.Destination == Node::getData(&BFSMap[ii], xx).Destination) {
					Node::deleteNode(&BFSMap[ii], xx);
				}
			}
		}
	}
	else
	{
		Node::deleteRight(&path);
	}
	draw();
}

IDSBoard::IDSBoard()
{

}
void IDSBoard::draw()
{

}
void IDSBoard::update()
{

}