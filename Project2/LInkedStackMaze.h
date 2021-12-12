#pragma once

#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include<fstream>

#include "LinkedStack.h"
#include "data.h"

using namespace std;
class DFSMaze {
private:

	int row;
	int col;
	char** map;
	LinkedStack stack1;
	Stack stack2;
	Stack stack3;
	Location2D exit;
public:
	DFSMaze()
	{
		init(0, 0);
	}
	void init(int r, int c) //맵 2차원 배열을 동적으로 할당
	{
		map = new char* [c];
		for (int i = 0; i < c; i++)
			map[i] = new char[r];
	}
	void reset() //map 동적으로 해제
	{
		for (int i = 0; i < col; i++)
			delete[] map[i];
		delete[] map;
	}
	void load(const char* fname) //미로 파일 불러오기
	{
		int start = 1; //1이면 출발점 2이면 도착점
		char c;
		char temp;
		row = 1;
		col = 0;
		FILE* fp;

		fp = fopen(fname, "r");
		if (fp == NULL)
			printf("Error : 파일이 존재하지 않습니다");
		while ((c = getc(fp)) != EOF)
		{
			col++;
			if (c == '\n')
				row++;
		}
		col = col / row;
		fclose(fp);

		LinkedStackMazeProjection = new char* [row];

		for (int i = 0; i < row; i++)
			LinkedStackMazeProjection[i] = new char[col];

		init(col, row);   //row행 col열 2차원 배열을 생성
		ifstream fin(fname, ios::in);    //fname파일을 읽어들임

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				fin >> temp;
				map[i][j] = temp;
				if (map[i][j] == '0' && start == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1)) //출발점 좌표일 경우
				{
					Location2D entry(i, j);
					stack2.push(entry);
					// printf(" 출발점 : (%d, %d) ", entry.getRow(), entry.getCol());
					start++;
					map[i][j] = '3'; //출발점을 이미 방문한 길과 구분하기 위해 3으로 지정
					// printf("\n");
				}
				else if (map[i][j] == '0' && start == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))//도착점 좌표일 경우
				{
					exit.setCol(j);
					exit.setRow(i);
					// printf(" 도착점 : (%d, %d) ", exit.getCol(), exit.getRow());
					map[i][j] = '9'; //도착점은 9로 지정
					// printf("\n");
				}
			}

		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				LinkedStackMazeProjection[i][j] = map[i][j];

				// printf("%c ", LinkedStackMazeProjection[i][j]);
			}

			//printf("\n");
		}

		fin.close();
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= row || c >= col) //미로의 범위를 벗어나면 false
			return false;
		else
			return (map[r][c] == '0' || map[r][c] == '9'); //통로이거나 도착점일 경우 true
	}

	void print()
	{
		int start = 1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//가장 처음으로 0을 만나면 출발점으로 설정
				if (map[i][j] == '0' && start == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))
				{
					printf("E");
					start++;
				}
				//미로가 갈 수 있는 길
				else if (map[i][j] == '0' && ((i != 0 && i != row - 1) && (j != 0 && j != col - 1)))
					printf("  ");
				//도착점
				else if (map[i][j] == '0' && start == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))
					printf("x");
				else if (map[i][j] == '1')
					printf("■");
				else if (map[i][j] == '5') //분기점
					printf("* ");
				else if (map[i][j] == '7') //지나간 길
					printf(" .");
				else if (map[i][j] == '9') //출구
					printf("X");
			}
			printf("\n");
		}
	}

	void searchExit(CoordinateQueue* CQueue)
	{
		FILE* writeMaze;
		writeMaze = fopen("print.txt", "w");
		fprintf(writeMaze, "< DFS로 미로 탐색 >\n");
		fprintf(writeMaze, "분기점을 만날 때까지 경로 출력\n");
		int count = 0;

		while (!stack2.isEmpty())
		{
			Location2D here = stack2.pop();
			stack3.push(here);
			int r = here.getRow();
			int c = here.getCol();
			if (map[r][c] != '3' || map[r][c] != '9') //stack3의 최상단 요소가 출발점이나 도착점이 아닐 경우 지나간 길로 설정
				map[r][c] = '7';

			//도착점에 도달했을 경우
			if (exit.getRow() == r && exit.getCol() == c)
			{
				while (!stack3.isEmpty())
				{
					Node* n = new Node(stack3.peek().getRow(), stack3.peek().getCol());
					stack1.push(n);
					stack3.pop();
				}
				while (!stack1.isEmpty())
				{
					// printf("(%d, %d) ", stack1.peek()->getRow(), stack1.peek()->getCol());

					element coordinate = { stack1.peek()->getRow() , stack1.peek()->getCol() };

					CQueue->enqueue(&coordinate);

					fprintf(writeMaze, "(%d, %d) ", stack1.peek()->getRow(), stack1.peek()->getCol());
					stack1.pop();
				}
				fprintf(writeMaze, "\n");
				fclose(writeMaze);
				// printf("\n 도착! \n");
				return;
			}
			else
			{
				if (isValidLoc(r - 1, c))
				{
					stack2.push(Location2D(r - 1, c));
					count++;
				}
				if (isValidLoc(r, c - 1))
				{
					stack2.push(Location2D(r, c - 1));
					count++;
				}
				if (isValidLoc(r + 1, c))
				{
					stack2.push(Location2D(r + 1, c));
					count++;
				}
				if (isValidLoc(r, c + 1))
				{
					stack2.push(Location2D(r, c + 1));
					count++;
				}

				if (count >= 2)
				{
					map[r][c] = '5';
					while (!stack3.isEmpty())
					{
						Node* n = new Node(stack3.peek().getRow(), stack3.peek().getCol());
						stack1.push(n);
						stack3.pop();
					}
					while (!stack1.isEmpty())
					{
						if (map[stack1.peek()->getRow()][stack1.peek()->getCol()] == '3')
						{
							printf("출발\n");
							printf("분기점을 만날 때까지 경로 출력\n");
						}

						element coordinateF = { stack1.peek()->getRow() , stack1.peek()->getCol() };

						// printf("(%d, %d) ", coordinateF.r, coordinateF.c);

						CQueue->enqueue(&coordinateF);
						fprintf(writeMaze, "(%d, %d) ", stack1.peek()->getRow(), stack1.peek()->getCol());
						stack1.pop();
					}
					// printf(" * ");
					fprintf(writeMaze, "\n");
					// printf("\n");
				}
				count = 0;
			}
		}
	}

	void dfsMaze()
	{
		printf("\n");
		printf("==== DFS 미로 찾기 ====\n");
		printf("( 이웃 위치 탐색 순서 )\n");
		printf("(1) ↑\n");
		printf("(2) ←\n");
		printf("(3) ↓\n");
		printf("(4) →\n");
		printf("\n");
	}

	void ExecuteLinkedStackFindPath(CoordinateQueue* CQueue)
	{
		load("maze.txt");
		// print();
		// dfsMaze();
		searchExit(CQueue);
		// print();
	}

	void deleteLinkedStackeMazeProj()
	{
		for (int i = 0; i < size_M; i++)
		{
			delete[] LinkedStackMazeProjection[i];
		}

		delete[] LinkedStackMazeProjection;
	}
};
