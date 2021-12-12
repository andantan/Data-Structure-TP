#include <cstdio>
#include <cstdlib>

#include <Windows.h>

#include "data.h"
#include "CoordinateQueue.h"

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif // !MAX_SIZE

#ifndef MAZE_SIZE
#define MAZE_SIZE 10
#endif // !MAZE_SIZE

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1','1','1','1','1'}, 
	{'M','0','0','0','1','0','0','0','0','1'}, 
	{'1','0','0','0','1','0','0','1','0','1'}, 
	{'1','0','1','1','1','0','0','1','0','1'}, 
	{'1','0','0','0','1','0','0','1','0','1'}, 
	{'1','0','1','0','1','0','0','1','0','1'}, 
	{'1','0','1','0','1','0','0','1','0','1'}, 
	{'1','0','1','0','1','0','0','1','0','1'}, 
	{'1','0','1','0','0','0','0','1','0','X'}, 
	{'1','1','1','1','1','1','1','1','1','1'} 
};

char mazeProj[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1','1','1','1','1'},
	{'M','0','0','0','1','0','0','0','0','1'},
	{'1','0','0','0','1','0','0','1','0','1'},
	{'1','0','1','1','1','0','0','1','0','1'},
	{'1','0','0','0','1','0','0','1','0','1'},
	{'1','0','1','0','1','0','0','1','0','1'},
	{'1','0','1','0','1','0','0','1','0','1'},
	{'1','0','1','0','1','0','0','1','0','1'},
	{'1','0','1','0','0','0','0','1','0','X'},
	{'1','1','1','1','1','1','1','1','1','1'}
}; // Projection of Mouse's moving onto mazeProj

//char maze[MAZE_SIZE][MAZE_SIZE] = { {'1','1','1','1','1'},
//								 {'M','0','1','0','1'},
//								 {'1','0','0','0','1'},
//								 {'1','1','1','0','X'},
//								 {'1','1','1','1','1'} };
//
//char mazeProj[MAZE_SIZE][MAZE_SIZE] = { {'1','1','1','1','1'},
//								 {'M','0','1','0','1'},
//								 {'1','0','0','0','1'},
//								 {'1','1','1','0','X'},
//								 {'1','1','1','1','1'} };

void init(Stack* p)
{
	p->top = -1;
}

bool isFull(Stack* p)
{
	return (p->top == MAX_SIZE - 1);
}

bool isEmpty(Stack* p)
{
	return (p->top == -1);
}

void push(Stack* p, Coordinate data)
{
	if (isFull(p)) printf("STACK IS FULL.\n");
	else
	{
		p->top++;

		p->data[p->top].x = data.x;
		p->data[p->top].y = data.y;
	}
}

Coordinate pop(stack* p)
{
	if (isEmpty(p))
	{
		printf("STACK IS EMPTY.\n");
	}

	return p->data[(p->top)--];
}

void Crawl(Stack* p, int x, int y)
{
	if (x < 0 || y < 0 ||
		MAZE_SIZE < x || MAZE_SIZE < y) return;
	
	if (maze[x][y] != '1' && maze[x][y] != '.')
	{
		Coordinate tmp;

		tmp.x = x;
		tmp.y = y;

		push(p, tmp);
	}
}

void printMaze()
{
	system("cls");

	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			if (mazeProj[i][j] == '0') printf("¡à");
			else if (mazeProj[i][j] == '1') printf("¡á");
			else if (mazeProj[i][j] == 'M' || mazeProj[i][j] == 'R') printf("¢º");
			else if (mazeProj[i][j] == 'L') printf("¢¸");
			else if (mazeProj[i][j] == 'U') printf("¡ã");
			else if (mazeProj[i][j] == 'D') printf("¡å");
			else if (mazeProj[i][j] == '.') printf("¢Á");
			else printf("¢Æ");
		}

		printf("\n");
	}
}

void WhereIsMouse(Coordinate* beforeCoordinate, Coordinate* afterCoordinate)
{
	short beforeMouseX = beforeCoordinate->x;
	short beforeMouseY = beforeCoordinate->y;
	short afterMouseX = afterCoordinate->x;
	short afterMouseY = afterCoordinate->y;

	if ((afterMouseX - beforeMouseX) > 0 && !(afterMouseY - beforeMouseY))
	{
		mazeProj[beforeMouseX][beforeMouseY] = '.';
		mazeProj[afterMouseX][afterMouseY] = 'D';
	}
	else if ((afterMouseX - beforeMouseX) < 0 && !(afterMouseY - beforeMouseY))
	{
		mazeProj[beforeMouseX][beforeMouseY] = '.';
		mazeProj[afterMouseX][afterMouseY] = 'U';
	}
	else if (!(afterMouseX - beforeMouseX) && (afterMouseY - beforeMouseY) > 0)
	{
		mazeProj[beforeMouseX][beforeMouseY] = '.';
		mazeProj[afterMouseX][afterMouseY] = 'R';
	}
	else if (!(afterMouseX - beforeMouseX) && (afterMouseY - beforeMouseY) < 0)
	{
		mazeProj[beforeMouseX][beforeMouseY] = '.';
		mazeProj[afterMouseX][afterMouseY] = 'L';
	}

	printMaze();

	printf("(%d, %d) -> (%d, %d)\n", beforeMouseX, beforeMouseY, afterMouseX, afterMouseY);
}

int main()
{
	Stack* s = new Stack();
	Coordinate currentCoordinate= { -1, -1 };
	Coordinate beforeCoordinate;

	CoordinateQueue queue;

	int i, j, x, y;

	init(s);

	for (i = 0; i < MAZE_SIZE; i++)
	{
		for (j = 0; j < MAZE_SIZE; j++)
		{
			if (maze[i][j] == 'M')
			{
				currentCoordinate.x = i;
				currentCoordinate.y = j;

				queue.enqueue(&currentCoordinate);
			}
		}
	}

	printMaze();
	Sleep(500);

	while (maze[currentCoordinate.x][currentCoordinate.y] != 'X')
	{
		x = currentCoordinate.x;
		y = currentCoordinate.y;

		maze[x][y] = '.';

		Crawl(s, x + 1, y);
		Crawl(s, x - 1, y);
		Crawl(s, x, y + 1);
		Crawl(s, x, y - 1);

		if (isEmpty(s))
		{
			printf("FAILED\n");
			
			break;
		}
		else
		{
			beforeCoordinate.x = x;
			beforeCoordinate.y = y;

			currentCoordinate = pop(s);

			queue.enqueue(&currentCoordinate);

			WhereIsMouse(&beforeCoordinate, &currentCoordinate);

			Sleep(500);
		}
	}

	queue.display();

	delete s;

	return 0;
}