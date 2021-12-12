#pragma once

#ifndef MAX
#define MAX 1000
#endif // !MAX

#include <cstdio>
#include <cstdlib>

char** LinkedQueueMazeProjection;
char** LinkedStackMazeProjection;

struct element {
	int r;//row Çà
	int c;//column ¿­
};

element ErrorCoordinate = { -1, -1 };

class CoordinateQueue
{
	int front;
	int rear;

	element data[MAX];

public:
	CoordinateQueue() : front(0), rear(0) { }

	bool QisEmpty() { return front == rear; }
	bool QisFull() { return (rear + 1) % MAX == front; }

	void enqueue(element* coordinate)
	{
		if (QisFull()) return;
		else
		{
			rear = (rear + 1) % MAX;

			data[rear].r = coordinate->r;
			data[rear].c = coordinate->c;
		}
	}

	element dequeue()
	{
		if (QisEmpty())
		{
			return ErrorCoordinate;
		}
		else
		{
			front = (front + 1) % MAX;

			return data[front];
		}
	}

	element peek()
	{
		if (QisEmpty())
		{
			return ErrorCoordinate;
		}
		else
		{
			return data[(front + 1) % MAX];
		}
	}

	void display()
	{
		int maxi = (front < rear) ? rear : rear + MAX;

		for (int i = front + 1; i <= maxi; i++)
		{
			if (!(data[i % MAX].r < 0))
				printf("(%d, %d) -> ", data[i % MAX].r, data[i % MAX].c);
		}

		printf("µµÂø\n");
	}
};