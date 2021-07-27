#include "GraphicalInterface.h"
GraphicalInterface::GraphicalInterface() {
	this->sb = SelectionBoard();
	this->initializing = true;
}
void GraphicalInterface::draw(GLFWwindow* window) {
	if (this->initializing) {
		this->sb.draw(window);
	}
	else {
		this->bfs.draw(window);
		this->dfs.draw(window);
		this->ids.draw(window);
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
	short startingPoint = this->sb.getStartingPoint();
	short endingPoint   = this->sb.getEndingPoint();
	this->bfs = BFSBoard(startingPoint, endingPoint);
	this->dfs = DFSBoard(startingPoint, endingPoint);
	this->ids = IDSBoard(startingPoint, endingPoint);
	this->initializing = false;
}
bool GraphicalInterface::isMore() {
	return (!this->bfs.isDone() || !this->dfs.isDone() || !this->ids.isDone() || this->initializing);
}
void GraphicalInterface::run(GLFWwindow* window) {
	if (this->isMore()) {
		this->update();
		this->draw(window);
	}
	
}