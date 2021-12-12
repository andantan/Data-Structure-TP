#pragma once

#include <cstdio>

struct Location2D {
	int row;
	int col;
	Location2D(int r = 0, int c = 0) { row = r; col = c; }
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int i) { row = i; }
	void setCol(int i) { col = i; }
	bool isNeighbor(Location2D& p) {
		return((row == p.row && (col == p.col - 1 || col == p.col + 1)) || (col == p.col && (row == p.row - 1 || row == p.row + 1)));
	}
	bool operator==(Location2D& p) { return row == p.row && col == p.col; }
	void display()
	{
		printf("( %d, %d )", row, col);
	}
};