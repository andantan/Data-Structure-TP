#pragma once

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif // !MAX_SIZE

typedef struct coordinate
{
	short x;
	short y;
} Coordinate;

typedef struct stack
{
	Coordinate data[MAX_SIZE];

	int top;
} Stack;