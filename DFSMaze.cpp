#include "DFSMaze.h"

int main()
{
	DFSMaze maze;
	maze.load("maze.txt");
	//maze.print();
	maze.dfsMaze();
	maze.searchExit();
	//maze.print();

	return 0;
}