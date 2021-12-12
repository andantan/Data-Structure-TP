#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX 100

struct element {
	int r;//row ��
	int c;//column ��
};

struct StackNode {
	element item;
	struct StackNode* link;
};

struct LinkedStack {
	StackNode* top;
};
//�ʱ�ȭ �Լ�
void S_init(LinkedStack* s)
{
	s->top = NULL;
}
//���� ����ִ��� Ȯ���ϴ� �Լ�
int S_isEmpty(LinkedStack* s)
{
	return (s->top == NULL);
}
//���� �Լ�
void push(LinkedStack* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		printf("�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
		return;
	}
	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
//�����Լ�
element pop(LinkedStack* s)
{
	element item;
	if (S_isEmpty(s)) {
		printf("������ ����ֽ��ϴ�.\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
//QueueNode
typedef struct QueueNode
{
	element item;
	struct QueueNode* link;
};

typedef struct LinkedQueue
{
	QueueNode* front;
	QueueNode* rear;
};
//���� �Լ�
void error(const char* message)
{
	printf("%s\n", message);
	exit(1);
}
//�ʱ�ȭ �Լ�
void init(LinkedQueue* q) {
	q->front = q->rear = 0;
}
// queue�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(LinkedQueue* q)
{
	return (q->front == NULL);
}
//��ȭ�������� Ȯ���ϴ� �Լ�
int is_full(LinkedQueue* q)
{
	return 0;
}
//���� �Լ�
void enqueue(LinkedQueue* q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
	{
		error("�޸𸮸� �Ҵ��� �� �����ϴ�.");
	}
	else {
		temp->item = item;
		temp->link = NULL;
		if (isEmpty(q)) {
			q->front = temp;
			q->rear = temp;
		}
		else {
			q->rear->link = temp;
			q->rear = temp;
		}
	}

}
//�����Լ�
element dequeue(LinkedQueue* q)
{
	QueueNode* temp = q->front;
	element item;

	if (isEmpty(q))
		error("ť�� ����ֽ��ϴ�.");
	else
	{
		item = temp->item;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
	}
	return item;
}
element start, here;
char** maze;
int** tmaze;

//��ο� ���ڸ� ���� ����.
//��ġť
void enqueue_loc(LinkedQueue* q, int r, int c, int n)
{
	if (r < 0 || c < 0) return; //0���� ������ ����
	if (maze[r][c] != '1' && maze[r][c] != '.') { //���̰ų� ������ �ڸ��� �ƴ� ���
		element tmp;
		tmp.r = r;
		tmp.c = c;

		enqueue(q, tmp);
		tmaze[r][c] = n + 1;
	}
}
void main()
{
	FILE* op;
	int r, c;
	int maze_col_size = 1, maze_row_size = 0, maze_size = 0;
	int cnt = 0;
	char* temp, maze_data[MAX];
	int i, j;

	LinkedStack s;
	LinkedQueue q;

	fopen_s(&op, "input.txt", "r+");

	fgets(maze_data, MAX, op);

	temp = strtok(maze_data, " ");
	//row ���� ���� ����
	while (temp != NULL)
	{
		temp = strtok(NULL, " ");
		maze_row_size++;
	}

	//column���� ���� ����
	while (fgets(maze_data, MAX, op) != NULL) {
		maze_col_size++;
	}
	fclose(op);

	maze_size = maze_col_size;


	fopen_s(&op, "input.txt", "r+");

	//input���� ����� �о���̱�����
   //�Ա�'e'�� �ⱸ'x'�� �о���̱� ���� �����Ҵ�
	maze = (char**)malloc(sizeof(char) * maze_size);
	for (i = 0; i <= maze_size - 1; i++)
		maze[i] = (char*)malloc(sizeof(char) * maze_size);

	tmaze = (int**)malloc(sizeof(int) * maze_size);
	for (i = 0; i <= maze_size - 1; i++)
		tmaze[i] = (int*)malloc(sizeof(int) * maze_size);

	for (i = 0; i < maze_size - 1; i++)
		for (j = 0; j < maze_size - 1; j++)
			tmaze[i][j] = 0;


	for (i = 0; i <= maze_size - 1; i++)
	{//����� ������ �迭�� ����.                                            
		fgets(maze_data, MAX, op);

		temp = strtok(maze_data, " ");
		maze[i][0] = temp[0];
		//������ġ ã��.
		if (temp[0] == 'e')
		{
			start.r = i;
			start.c = 0;
		}
		for (j = 1; j <= maze_size - 1; j++)
		{
			temp = strtok(NULL, " ");
			maze[i][j] = temp[0];

			if (temp[0] == 'e')
			{
				start.r = i;
				start.c = j;
			}
		}
	}

	here = start;

	fclose(op);

	init(&q);

	printf("ť�� �̿��� �̷�ã�� ����.\n\n");
	printf("Enter(%d, %d)��", start.r, start.c);
	while (maze[here.r][here.c] != 'x') {  //�ⱸ�� �ƴϸ�
		r = here.r;
		c = here.c;

		
		maze[r][c] = '.'; //�����ڸ��� ������'.' ó��
		
		enqueue_loc(&q, r - 1, c, tmaze[r][c]);
		enqueue_loc(&q, r + 1, c, tmaze[r][c]);
		enqueue_loc(&q, r, c - 1, tmaze[r][c]);
		enqueue_loc(&q, r, c + 1, tmaze[r][c]);

		if (isEmpty(&q))
			return;
		else
			here = dequeue(&q);
	}
	S_init(&s);
	push(&s, here);

	//������� ���ڷ� �ִ� ��� Ž�� �������� ó��
	while (here.r != start.r && here.c != start.c) {
		if (tmaze[here.r][here.c] - 1 == tmaze[here.r][here.c + 1])
			here.c = here.c + 1; //�Ʒ��� ��ĭ
		else if (tmaze[here.r][here.c] - 1 == tmaze[here.r][here.c - 1])
			here.c = here.c - 1; //���� ��ĭ
		else if (tmaze[here.r][here.c] - 1 == tmaze[here.r + 1][here.c])
			here.r = here.r + 1; //���������� ��ĭ
		else if (tmaze[here.r][here.c] - 1 == tmaze[here.r - 1][here.c])
			here.r = here.r - 1; //�������� ��ĭ
		push(&s, here);
	}
	pop(&s);
	printf("(%d, %d)��", here.r, here.c);
	while (!(S_isEmpty(&s))) {
		element temps;
		temps = pop(&s);
		printf("(%d, %d)��", temps.r, temps.c);
		cnt++;
		if (cnt % 10 == 0) printf("\n");
	}
	printf("Exit\n");
	printf("\n�̷�ã�� �Ϸ�.\n");
}