/**
 * Chandlor Ratcliffe has Authored the terminal interface
 */
#include <iostream>
#include "constants.h"
#include "Board.h"

/**
* The issue of our error is this function! The passing of the function kept deleting our map data.
* The solution was to pass the data by address so we do not lose the map data.
*/
bool complete(DFSBoard* d, BFSBoard* b, IDSBoard* i) {
	return d->isDone() && b->isDone() && i->isDone();
}
void mainRun() {
	short choice;
	for (short i = 0; i < 20; ++i)
		std::cout << i << ": " << CityDat(i, 0) << std::endl;
	std::cout << "From the above, select a starting city by number: ";
	std::cin >> choice;
	DFSBoard dfs(choice);
	BFSBoard bfs(choice);
	IDSBoard ids(choice);
	while (!complete(&dfs, &bfs, &ids)) {
		if (!dfs.isDone()) { dfs.update(); dfs.draw(); }
		if (!bfs.isDone()) { bfs.update(); bfs.draw(); }
		if (!ids.isDone()) { ids.update(); ids.draw(); }
	}
	std::cout << endl << "DFS FINAL:";
	dfs.draw();
	std::cout << endl << "BFS FINAL:";
	bfs.draw();
	std::cout << endl << "IDS FINAL:";
	ids.draw();
}
int main()
{
	mainRun();
	return 0;
}