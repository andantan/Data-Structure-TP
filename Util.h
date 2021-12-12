#pragma once

#include "data.h"

#ifndef MAX_SIZE
#define MAX_SIZE 10
#endif // !MAX_SIZE

void printQueueVersionMaze()
{
	system("cls");

	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (LinkedQueueMazeProjection[i][j] == '0') printf("¡à");
			else if (LinkedQueueMazeProjection[i][j] == 'e') printf("¡Ü");
			else if (LinkedQueueMazeProjection[i][j] == '1') printf("¡á");
			else if (LinkedQueueMazeProjection[i][j] == 'R') printf("¢º");
			else if (LinkedQueueMazeProjection[i][j] == 'L') printf("¢¸");
			else if (LinkedQueueMazeProjection[i][j] == 'U') printf("¡ã");
			else if (LinkedQueueMazeProjection[i][j] == 'D') printf("¡å");
			else if (LinkedQueueMazeProjection[i][j] == '.') printf("¢Á");
			else printf("¢Æ");
		}

		printf("\n");
	}
}

void printStackVersionMaze()
{
	system("cls");

	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (LinkedStackMazeProjection[i][j] == '0') printf("¡à");
			else if (LinkedStackMazeProjection[i][j] == '3') printf("¡Ü");
			else if (LinkedStackMazeProjection[i][j] == '1') printf("¡á");
			else if (LinkedStackMazeProjection[i][j] == 'R') printf("¢º");
			else if (LinkedStackMazeProjection[i][j] == 'L') printf("¢¸");
			else if (LinkedStackMazeProjection[i][j] == 'U') printf("¡ã");
			else if (LinkedStackMazeProjection[i][j] == 'D') printf("¡å");
			else if (LinkedStackMazeProjection[i][j] == '.') printf("¢Á");
			else printf("¢Æ");
		}

		printf("\n");
	}
}

void WhereIsMouseQueueVersion(element* beforeCoordinate, element* afterCoordinate)
{
	short beforeMouseX = beforeCoordinate->r;
	short beforeMouseY = beforeCoordinate->c;
	short afterMouseX = afterCoordinate->r;
	short afterMouseY = afterCoordinate->c;

	if ((afterMouseX - beforeMouseX) > 0 && !(afterMouseY - beforeMouseY))
	{
		LinkedQueueMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedQueueMazeProjection[afterMouseX][afterMouseY] = 'D';
	}
	else if ((afterMouseX - beforeMouseX) < 0 && !(afterMouseY - beforeMouseY))
	{
		LinkedQueueMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedQueueMazeProjection[afterMouseX][afterMouseY] = 'U';
	}
	else if (!(afterMouseX - beforeMouseX) && (afterMouseY - beforeMouseY) > 0)
	{
		LinkedQueueMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedQueueMazeProjection[afterMouseX][afterMouseY] = 'R';
	}
	else if (!(afterMouseX - beforeMouseX) && (afterMouseY - beforeMouseY) < 0)
	{
		LinkedQueueMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedQueueMazeProjection[afterMouseX][afterMouseY] = 'L';
	}

	printQueueVersionMaze();
	

	printf("(%d, %d) -> (%d, %d)\n", beforeMouseX, beforeMouseY, afterMouseX, afterMouseY);
}

void WhereIsMouseStackVersion(element* beforeCoordinate, element* afterCoordinate)
{
	short beforeMouseX = beforeCoordinate->r;
	short beforeMouseY = beforeCoordinate->c;
	short afterMouseX = afterCoordinate->r;
	short afterMouseY = afterCoordinate->c;

	if ((afterMouseX - beforeMouseX) > 0 && !(afterMouseY - beforeMouseY))
	{
		LinkedStackMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedStackMazeProjection[afterMouseX][afterMouseY] = 'D';
	}
	else if ((afterMouseX - beforeMouseX) < 0 && !(afterMouseY - beforeMouseY))
	{
		LinkedStackMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedStackMazeProjection[afterMouseX][afterMouseY] = 'U';
	}
	else if (!(afterMouseX - beforeMouseX) && (afterMouseY - beforeMouseY) > 0)
	{
		LinkedStackMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedStackMazeProjection[afterMouseX][afterMouseY] = 'R';
	}
	else if (!(afterMouseX - beforeMouseX) && (afterMouseY - beforeMouseY) < 0)
	{
		LinkedStackMazeProjection[beforeMouseX][beforeMouseY] = '.';
		LinkedStackMazeProjection[afterMouseX][afterMouseY] = 'L';
	}

	printStackVersionMaze();

	printf("(%d, %d) -> (%d, %d)\n", beforeMouseX, beforeMouseY, afterMouseX, afterMouseY);
}