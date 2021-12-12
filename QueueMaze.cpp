#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX 100

struct element {
	int r;//row 행
	int c;//column 열
};

struct StackNode {
	element item;
	struct StackNode* link;
};

struct LinkedStack {
	StackNode* top;
};
//초기화 함수
void S_init(LinkedStack* s)
{
	s->top = NULL;
}
//스택 비어있는지 확인하는 함수
int S_isEmpty(LinkedStack* s)
{
	return (s->top == NULL);
}
//삽입 함수
void push(LinkedStack* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		printf("메모리를 할당할 수 없습니다.\n");
		return;
	}
	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
//삭제함수
element pop(LinkedStack* s)
{
	element item;
	if (S_isEmpty(s)) {
		printf("스택이 비어있습니다.\n");
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
//오류 함수
void error(const char* message)
{
	printf("%s\n", message);
	exit(1);
}
//초기화 함수
void init(LinkedQueue* q) {
	q->front = q->rear = 0;
}
// queue가 비어있는지 확인하는 함수
int isEmpty(LinkedQueue* q)
{
	return (q->front == NULL);
}
//포화상태인지 확인하는 함수
int is_full(LinkedQueue* q)
{
	return 0;
}
//삽입 함수
void enqueue(LinkedQueue* q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
	{
		error("메모리를 할당할 수 없습니다.");
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
//삭제함수
element dequeue(LinkedQueue* q)
{
	QueueNode* temp = q->front;
	element item;

	if (isEmpty(q))
		error("큐가 비어있습니다.");
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

//경로에 숫자를 집어 넣음.
//위치큐
void enqueue_loc(LinkedQueue* q, int r, int c, int n)
{
	if (r < 0 || c < 0) return; //0보다 작으면 리턴
	if (maze[r][c] != '1' && maze[r][c] != '.') { //벽이거나 지나온 자리가 아닐 경우
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
	//row 열의 개수 세기
	while (temp != NULL)
	{
		temp = strtok(NULL, " ");
		maze_row_size++;
	}

	//column행의 개수 세기
	while (fgets(maze_data, MAX, op) != NULL) {
		maze_col_size++;
	}
	fclose(op);

	maze_size = maze_col_size;


	fopen_s(&op, "input.txt", "r+");

	//input에서 행렬을 읽어들이기위해
   //입구'e'와 출구'x'를 읽어들이기 위해 동적할당
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
	{//행렬의 정보를 배열에 저장.                                            
		fgets(maze_data, MAX, op);

		temp = strtok(maze_data, " ");
		maze[i][0] = temp[0];
		//시작위치 찾기.
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

	printf("큐를 이용한 미로찾기 시작.\n\n");
	printf("Enter(%d, %d)→", start.r, start.c);
	while (maze[here.r][here.c] != 'x') {  //출구가 아니면
		r = here.r;
		c = here.c;

		
		maze[r][c] = '.'; //현재자리를 지나옴'.' 처리
		
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

	//집어넣은 숫자로 최단 경로 탐색 역순으로 처리
	while (here.r != start.r && here.c != start.c) {
		if (tmaze[here.r][here.c] - 1 == tmaze[here.r][here.c + 1])
			here.c = here.c + 1; //아래로 한칸
		else if (tmaze[here.r][here.c] - 1 == tmaze[here.r][here.c - 1])
			here.c = here.c - 1; //위로 한칸
		else if (tmaze[here.r][here.c] - 1 == tmaze[here.r + 1][here.c])
			here.r = here.r + 1; //오른쪽으로 한칸
		else if (tmaze[here.r][here.c] - 1 == tmaze[here.r - 1][here.c])
			here.r = here.r - 1; //왼쪽으로 한칸
		push(&s, here);
	}
	pop(&s);
	printf("(%d, %d)→", here.r, here.c);
	while (!(S_isEmpty(&s))) {
		element temps;
		temps = pop(&s);
		printf("(%d, %d)→", temps.r, temps.c);
		cnt++;
		if (cnt % 10 == 0) printf("\n");
	}
	printf("Exit\n");
	printf("\n미로찾기 완료.\n");
}