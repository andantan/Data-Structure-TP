#pragma once

#include <cstdio>
#include <cstdlib>

#include "data.h"

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif // !MAX_SIZE


class CoordinateQueue
{
	int front;
	int rear;
	
	Coordinate data[MAX_SIZE];

public:
	CoordinateQueue() : front(0), rear(0) { }

	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_SIZE == front; }

	void enqueue(Coordinate* coordinate)
	{
		if (isFull()) printf("QUEUE IS FULL.\n");
		else
		{
			rear = (rear + 1) % MAX_SIZE;

			data[rear].x = coordinate->x;
			data[rear].y = coordinate->y;
		}
	}

	Coordinate dequeue()
	{
		if (isEmpty())
		{
			printf("QUEUE IS EMPTY.\n");
		}
		else
		{
			front = (front + 1) % MAX_SIZE;

			return data[front];
		}
	}

	void display()
	{
		int maxi = (front < rear) ? rear : rear + MAX_SIZE;

		for (int i = front + 1; i <= maxi; i++)
		{
			printf("(%d, %d) -> ", data[i % MAX_SIZE].x, data[i % MAX_SIZE].y);
		}

		printf("ARRIVED\n");
	}
};
