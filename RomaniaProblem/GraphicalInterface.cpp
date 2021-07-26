#include "GraphicalInterface.h"
GraphicalInterface::GraphicalInterface() {
	this->sb = SelectionBoard();
	this->initializing = true;
}
void GraphicalInterface::draw() {
	if (this->initializing) {
		this->sb.draw();
	}
	else {
		this->bfs.draw();
		this->dfs.draw();
		this->ids.draw();
	}
}
void GraphicalInterface::update() {
	if (this->sb.makingChoices()) {
		this->sb.update();
		if (!this->sb.makingChoices()) this->init();
	}
	else {
		if (!this->bfs.isDone()) this->bfs.update();
		if (!this->dfs.isDone()) this->dfs.update();
		if (!this->ids.isDone()) this->ids.update();
	}
}
void GraphicalInterface::init() {
	City startingPoint = this->sb.getStartingPoint();
	City endingPoint   = this->sb.getEndingPoint();
	this->bfs = BFSBoard(startingPoint, endingPoint);
	this->dfs = DFSBoard(startingPoint, endingPoint);
	this->ids = IDSBoard(startingPoint, endingPoint);
	this->initializing = false;
}
bool GraphicalInterface::isMore() {
	return (!this->bfs.isDone() || !this->dfs.isDone() || !this->ids.isDone() || this->initializing);
}
void GraphicalInterface::run() {
	if (this->isMore()) {
		this->update();
		this->draw();
	}
	std::cout << "[INFO] PROGRAM COMPLETE." << std::endl;
}