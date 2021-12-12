#include "Location2D.h"
#include <cstdlib>

#define MAX_STACK_SIZE 1024

class Node : public Location2D
{
	Node* link;
public:
	Node(int row, int col) : Location2D(row, col) { link = NULL; }
	~Node(void) {}
	Node* getLink() { return link; }
	void setLink(Node* p) { link = p; }
};

inline void error(const char* str) {
	printf("%s", str);
	exit(1);
}

class Stack
{
	int top;
	Location2D data[MAX_STACK_SIZE];
public:
	Stack() { top = -1; }
	bool isEmpty() { return top == -1; }
	bool isFull() { return top + 1 == MAX_STACK_SIZE; }

	void push(Location2D n) {
		if (isFull()) error("스택 포화 상태");
		else {
			data[++top] = n;
		}
	}
	Location2D pop() {
		if (isEmpty()) return NULL;
		return data[top--];
	}
	Location2D peek() {
		if (isEmpty()) return NULL;
		return data[top];
	}
};