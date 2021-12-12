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
	void init(int r, int c) //�� 2���� �迭�� �������� �Ҵ�
	{
		map = new char* [c];
		for (int i = 0; i < c; i++)
			map[i] = new char[r];
	}
	void reset() //map �������� ����
	{
		for (int i = 0; i < col; i++)
			delete[] map[i];
		delete[] map;
	}
	void load(const char* fname) //�̷� ���� �ҷ�����
	{
		int start = 1; //1�̸� ����� 2�̸� ������
		char c;
		char temp;
		row = 1;
		col = 0;
		FILE* fp;

		fp = fopen(fname, "r");
		if (fp == NULL)
			printf("Error : ������ �������� �ʽ��ϴ�");
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

		init(col, row);   //row�� col�� 2���� �迭�� ����
		ifstream fin(fname, ios::in);    //fname������ �о����

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				fin >> temp;
				map[i][j] = temp;
				if (map[i][j] == '0' && start == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1)) //����� ��ǥ�� ���
				{
					Location2D entry(i, j);
					stack2.push(entry);
					// printf(" ����� : (%d, %d) ", entry.getRow(), entry.getCol());
					start++;
					map[i][j] = '3'; //������� �̹� �湮�� ��� �����ϱ� ���� 3���� ����
					// printf("\n");
				}
				else if (map[i][j] == '0' && start == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))//������ ��ǥ�� ���
				{
					exit.setCol(j);
					exit.setRow(i);
					// printf(" ������ : (%d, %d) ", exit.getCol(), exit.getRow());
					map[i][j] = '9'; //�������� 9�� ����
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
		if (r < 0 || c < 0 || r >= row || c >= col) //�̷��� ������ ����� false
			return false;
		else
			return (map[r][c] == '0' || map[r][c] == '9'); //����̰ų� �������� ��� true
	}

	void print()
	{
		int start = 1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//���� ó������ 0�� ������ ��������� ����
				if (map[i][j] == '0' && start == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))
				{
					printf("E");
					start++;
				}
				//�̷ΰ� �� �� �ִ� ��
				else if (map[i][j] == '0' && ((i != 0 && i != row - 1) && (j != 0 && j != col - 1)))
					printf("  ");
				//������
				else if (map[i][j] == '0' && start == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))
					printf("x");
				else if (map[i][j] == '1')
					printf("��");
				else if (map[i][j] == '5') //�б���
					printf("* ");
				else if (map[i][j] == '7') //������ ��
					printf(" .");
				else if (map[i][j] == '9') //�ⱸ
					printf("X");
			}
			printf("\n");
		}
	}

	void searchExit(CoordinateQueue* CQueue)
	{
		FILE* writeMaze;
		writeMaze = fopen("print.txt", "w");
		fprintf(writeMaze, "< DFS�� �̷� Ž�� >\n");
		fprintf(writeMaze, "�б����� ���� ������ ��� ���\n");
		int count = 0;

		while (!stack2.isEmpty())
		{
			Location2D here = stack2.pop();
			stack3.push(here);
			int r = here.getRow();
			int c = here.getCol();
			if (map[r][c] != '3' || map[r][c] != '9') //stack3�� �ֻ�� ��Ұ� ������̳� �������� �ƴ� ��� ������ ��� ����
				map[r][c] = '7';

			//�������� �������� ���
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
				// printf("\n ����! \n");
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
							printf("���\n");
							printf("�б����� ���� ������ ��� ���\n");
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
		printf("==== DFS �̷� ã�� ====\n");
		printf("( �̿� ��ġ Ž�� ���� )\n");
		printf("(1) ��\n");
		printf("(2) ��\n");
		printf("(3) ��\n");
		printf("(4) ��\n");
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
