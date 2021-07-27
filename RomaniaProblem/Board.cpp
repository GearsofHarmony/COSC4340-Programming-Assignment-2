#include "Board.h"


BaseBoard::BaseBoard()
{
	// startNode and endNode is here temporarily I'll leave it to you to to initialize them elsewhere
	this->startNode = 0;
	this->endNode = 4;
	char file[] = { "input.txt" };
	int city1, city2, dist;
	fstream fin(file, ios::in);
	if (fin.is_open())
	{
		//std::cout << "input open, loading cities.." <<std::endl;
		while (fin.eof() == false)
		{
			fin >> city1 >> city2 >> dist;
			//std::cout << "Loading: " <<city1 <<", " << city2 << ": " << dist << CityDat(city2, dist) << std::endl;
			Node<CityDat>::insertRight(&Map[city1], new Nodeptr<CityDat>(CityDat(city2, dist)));
			Node<CityDat>::insertRight(&Map[city2], new Nodeptr<CityDat>(CityDat(city1, dist)));
		}
		fin.close();
	}
	else
		cout << "Error opening file: " << file << endl;
}
BaseBoard::BaseBoard(short startNode, short endNode)
{
	// startNode and endNode is here temporarily I'll leave it to you to to initialize them elsewhere
	this->startNode = startNode;
	this->endNode = endNode;
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
void BaseBoard::draw(GLFWwindow* window)
{
	/*for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "List " << ii << ": ";
		Node<CityDat>::printList(&Map[ii]);
	}*/
}
void BaseBoard::update() {};

SelectionBoard::SelectionBoard() {
}
void SelectionBoard::draw(GLFWwindow* window) {
	BaseBoard::draw(window);
}
void SelectionBoard::update() {

}
bool SelectionBoard::makingChoices() {
	return false;
}
short SelectionBoard::getStartingPoint() {
	return 0;
}
short SelectionBoard::getEndingPoint() {
	return 4;
}

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

	
}

DFSBoard::DFSBoard(short startingPoint, short endingPoint) {
	this->startNode = startingPoint;
	this->endNode = endingPoint;
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
}

void DFSBoard::draw(GLFWwindow* window)
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

	
}

BFSBoard::BFSBoard(short startingPoint, short endingPoint) {
	this->startNode = startingPoint;
	this->endNode = endingPoint;
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
}
void BFSBoard::draw(GLFWwindow* window)
{
	typedef Node<CityDat> Node;
	typedef Nodeptr<CityDat> Nodeptr;
	for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "List " << ii << ": ";
		Node::printList(&BFSMap[ii]);
	}
	cout << endl << "To Visit: ";
	Node::printList(&toVisit);
	for (int ii = 0; ii < MSIZE; ii++) {
		cout << endl << "Probe Path: ";
		Node::printList(&probePath[ii]);
	}
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
		if (curNode.Destination == endNode)
		{
			cout << "\nGoal Reached!\n";
			while (Node::isEmpty(&probePath[curNode.Destination]) == false)
			{
				Node::insertLeft(&path, new Nodeptr(curNode));
				curNode = Node::getData(&probePath[curNode.Destination], 0);
			}
			Node::insertLeft(&path, new Nodeptr(curNode));
			done = true;
		}
		else 
		{
			while (Node::isEmpty(&BFSMap[curNode.Destination]) == false)
			{
				CityDat probeNode = Node::getData(&BFSMap[curNode.Destination], 0);
				Node::insertRight(&toVisit, new Nodeptr(probeNode));
				Node::insertRight(&probePath[probeNode.Destination], new Nodeptr(curNode));
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
	else
	{
		for (int ii = 0; ii < MSIZE; ii++) {
			Node::deleteList(&BFSMap[ii]);
			for (int xx = 0; xx < Node::getSize(&Map[ii]); xx++) {
				if (startNode != Node::getData(&Map[ii], xx).Destination) {
					Node::insertRight(&BFSMap[ii], new Nodeptr(Node::getData(&Map[ii], xx)));
				}
			}
		}
	}

	
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

	
}
IDSBoard::IDSBoard(short startingPoint, short endingPoint) {
	this->startNode = short(startingPoint);
	this->endNode = short(endingPoint);

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
}

void IDSBoard::draw(GLFWwindow* window)
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

}