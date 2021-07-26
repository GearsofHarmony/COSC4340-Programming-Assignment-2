#include "Board.h"

BaseBoard::BaseBoard()
{
	// startNode and endNode is here temporarily I'll leave it to you to to initialize them elsewhere
	startNode = 0;
	endNode = 4;
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
		cout << "\nGoal Reached!\n";
		done = true;
	}
	else
	{
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
	cout << endl << "To Visit: ";
	Node::printList(&toVisit);
	cout << endl << "Path: ";
	Node::printList(&path);
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
		if (curNode.Destination == endNode)
		{
			cout << "\nGoal Reached!\n";
			done = true;
		}
		else 
		{
			if (Node::isEmpty(&BFSMap[curNode.Destination]) == true)
			{
				Node::deleteRight(&path);
			}
			while (Node::isEmpty(&BFSMap[curNode.Destination]) == false)
			{
				CityDat probeNode = Node::getData(&BFSMap[curNode.Destination], 0);
				Node::insertRight(&toVisit, new Nodeptr(probeNode));
				Node::deleteLeft(&BFSMap[curNode.Destination]);
				for (int ii = 0; ii < MSIZE; ii++) {
					for (int xx = 0; xx < Node::getSize(&BFSMap[ii]); xx++) {
						if (probeNode.Destination == Node::getData(&BFSMap[ii], xx).Destination) {
							Node::deleteNode(&BFSMap[ii], xx);
						}
					}
				}
			}
		}
	}

	draw();
}

IDSBoard::IDSBoard()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	depthLimit = 0;
	depth = 0;
	done = false;

	for (int ii = 0; ii < MSIZE; ii++) {
		for (int xx = 0; xx < Node::getSize(&Map[ii]); xx++) {
			if (startNode != Node::getData(&Map[ii], xx).Destination) {
				Node::insertRight(&IDSMap[ii], new Nodeptr(Node::getData(&Map[ii], xx)));
			}
		}
	}

	CityDat curNode(startNode, 0);
	Node::insertRight(&path, new Nodeptr(curNode));

	draw();
}
void IDSBoard::draw()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	cout << endl << "Depth Limit: " << depthLimit;
	cout << endl << "Depth: " << depth;
	for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "List " << ii << ": ";
		Node::printList(&IDSMap[ii]);
	}
	cout << endl << "Path: ";
	Node::printList(&path);
	cout << endl;
}
void IDSBoard::update()
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	CityDat curNode, probeNode;

	if (Node::isEmpty(&path) == false)
	{
		curNode = Node::getData(&path, Node::getSize(&path) - 1);
		if (curNode.Destination == endNode)
		{
			cout << "\nGoal Reached!\n";
			done = true;
		}
		else
		{
			if (depth > depthLimit)
			{
				Node::deleteRight(&path);
				depth -= curNode.Distance;
			}
			else if (Node::isEmpty(&IDSMap[curNode.Destination]) == false)
			{
				probeNode = Node::getData(&IDSMap[curNode.Destination], 0);
				Node::insertRight(&path, new Nodeptr(probeNode));
				Node::deleteLeft(&IDSMap[curNode.Destination]);

				depth += probeNode.Distance;

				for (int ii = 0; ii < MSIZE; ii++) {
					for (int xx = 0; xx < Node::getSize(&IDSMap[ii]); xx++) {
						if (probeNode.Destination == Node::getData(&IDSMap[ii], xx).Destination) {
							Node::deleteNode(&IDSMap[ii], xx);
						}
					}
				}
			}
			else
			{
				if (Node::getSize(&path) == 1)  // Rebuild map if at starting node and increase depth limit which is vital
				{
					for (int ii = 0; ii < MSIZE; ii++) {
						Node::deleteList(&IDSMap[ii]);
						for (int xx = 0; xx < Node::getSize(&Map[ii]); xx++) {
							if (startNode != Node::getData(&Map[ii], xx).Destination) {
								Node::insertRight(&IDSMap[ii], new Nodeptr(Node::getData(&Map[ii], xx)));
							}
						}
					}
					depthLimit += 75;
				}
				else
					Node::deleteRight(&path);
				depth -= curNode.Distance;
			}
		}
	}

	draw();
}