#include "LinkedQueueMaze.h"
#include "LInkedStackMaze.h"
#include "Util.h"
#include "data.h"

#include <Windows.h>

using namespace std;

int main()
{

	int select;

	cout << "1. LinkedStack을 이용한 경로찾기" << endl;
	cout << "2. LInkedQueue를 이용한 경로찾기(DFS)" << endl;

	cout << "선택: ";
	cin >> select;

	if (select == 1)
	{
		DFSMaze dfs;

		CoordinateQueue LinkedStackResultCoordinateQueue;

		element beforeCoordinate;
		element currenCoordinate;

		dfs.ExecuteLinkedStackFindPath(&LinkedStackResultCoordinateQueue);

		printStackVersionMaze();

		Sleep(500);

		while (!LinkedStackResultCoordinateQueue.QisEmpty())
		{
			beforeCoordinate = LinkedStackResultCoordinateQueue.dequeue();
			currenCoordinate = LinkedStackResultCoordinateQueue.peek();

			if (currenCoordinate.r == -1) break;

			WhereIsMouseStackVersion(&beforeCoordinate, &currenCoordinate);

			Sleep(100);
		}

		printf("\n");

		LinkedStackResultCoordinateQueue.display();

		dfs.deleteLinkedStackeMazeProj();
	}
	else
	{
		CoordinateQueue LinkedQueueResultCoordinateQueue;

		ExecuteLinkedQueueFindPath(&LinkedQueueResultCoordinateQueue);

		element beforeCoordinate;
		element currenCoordinate;


		printQueueVersionMaze();

		Sleep(500);

		while (!LinkedQueueResultCoordinateQueue.QisEmpty())
		{
			beforeCoordinate = LinkedQueueResultCoordinateQueue.dequeue();
			currenCoordinate = LinkedQueueResultCoordinateQueue.peek();

			if (currenCoordinate.r == -1) break;

			WhereIsMouseQueueVersion(&beforeCoordinate, &currenCoordinate);

			Sleep(100);
		}

		printf("\n");

		LinkedQueueResultCoordinateQueue.display();

		deleteLinkedQueueMazeProj();
	}

	return 0;
}