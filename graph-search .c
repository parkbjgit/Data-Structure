#include<stdio.h>
#include<stdlib.h>
#define FALSE 0 // visit flag로 사용
#define TRUE 1
#define MAX_VERTEX 10 // 최대 vertex의 수

typedef struct Node { //vertex 구조체
	int key;
	struct Node* link;
} listNode;

typedef struct graph {
	listNode* list[MAX_VERTEX]; // 그래프를 가리킬 구조체 포인터
	int ident[MAX_VERTEX]; // vertex의 존재 확인에 쓰이는 배열
}graph;

graph* Initialize(graph* h); // 그래프 초기화
void InsertVertex(graph* h, int key); // vertex 삽입
void InsertEdge(graph* h, int con1, int con2); // edge 연결
void printgraph(graph* h); // 그래프 출력
void dfs(graph* h, int key); // 깊이 우선 탐색
void bfs(graph* h, int key); // 너비 우선 탐색
void freegraph(graph* h); // 메모리 해제
int visited[MAX_VERTEX]; // 방문 확인 배열

listNode* queue[MAX_VERTEX]; // 너비우선 탐색에 쓰일 큐
listNode* deQueue(); // 삭제
void enQueue(listNode* aNode); // 삽입
int front = NULL;
int rear = NULL;

int main()
{
	graph* h = NULL;
	char command;
	int key;
	int con1, con2; // 연결하고자 하는 vertex_InsertEdge 함수에서 사용
    printf("---------------------2021041022 Park Beom Jun-------------------\n");
	do {
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                          Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z                              \n");
		printf(" Insert Vertex       = v     Insert Edge          = e \n");
		printf(" Depth First Search  = d     Breath First Search  = b \n");
		printf(" Print Graph         = p     Quit                 = q\n");
		printf("----------------------------------------------------------------\n");
   		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z': // 초기화
			h = Initialize(h); // 그래프를 초기화해서 h로 받기
			break;
		case 'v': case 'V': // vertex 삽입
			printf("Your Key(0~9) :");
			scanf("%d", &key);
			InsertVertex(h, key); // 초기화한 그래프에서 바로 연결
			break;
		case 'd': case 'D': // dfs
			printf("Your Key(0~9) :");
			scanf("%d", &key);
			dfs(h, key);
			for (int i = 0; i < MAX_VERTEX; i++) // 방문 배열을 초기화해줘야 dfs사용 가능
			{
				visited[i] = FALSE;
			}
			break;
		case 'p': case 'P': // 그래프 출력
			printgraph(h);
			break;
		case 'e': case 'E': // 간선 연결
			printf("Two vertex :");
			scanf("%d %d", &con1, &con2);
			InsertEdge(h, con1, con2);
			break;
		case 'b': case 'B': // bfs
			printf("Your Key(0~9) :");
			scanf("%d", &key);
			bfs(h, key);
			for (int i = 0; i < MAX_VERTEX; i++) // 방문 배열을 초기화해야 bfs 사용 가능
			{
				visited[i] = FALSE;
			}
			front = NULL;
			rear = NULL;
			break;
		case 'q': case 'Q': // 메모리 해제
			freegraph(h);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');
	return 1;
}

graph* Initialize(graph* h) // 그래프 초기화
{
	if (h != NULL) // 그래프가 비어있지 않다면,
	{
		freegraph(h->list); // 그래프 전체 초기화
		printf("초기화 한번 더 누르기");
		// 그래프를 다시 쓰려면, z를 한번 더 눌러서 공간 생성해야함
		return NULL;
	}
	else
	{
		graph* p = (graph*)malloc(sizeof(graph)); // 그래프 공간 할당
		for (int i = 0; i < MAX_VERTEX; i++)
		{
			p->list[i] = NULL; // 각 노드들을 이어줄 vertex 번호를 인덱스로하는 인접리스트 초기화
		}
		return p;
	}

}

void InsertVertex(graph* h, int key) // vertex 삽입
{
	h->ident[key] = 1; // 삽입된 vertex는 확인값을 주어 vertex의 존재성 확인
	if (key > 9 || key < 0) // vertex 번호, 개수 제한
		printf("숫자 초과함\n");
}

void InsertEdge(graph* h, int con1, int con2) // 간선 연결
{
	listNode* trail = NULL;
	listNode* trail2 = NULL;
	listNode* a = h->list[con2];

	if (h->ident[con1] != 1 || h->ident[con2] != 1) // vertex가 존재하는지 우선 확인
	{
		printf("vertex is not exist\n");
		return;
	}

	listNode* vertex1 = (listNode*)malloc(sizeof(listNode)); // 정점 생성하고 공간할당해주기
	vertex1->key = con1; // 값 할당
	vertex1->link = NULL;

	if (h->list[con2] == NULL) // 해당하는 인접 리스트가 아무것도 가리키고 있지 않으면
	{
		h->list[con2] = vertex1; // 바로 생성 vertex를 가리킴
	}
	else // 해당 인접리스트가 무언가를 가리키고 있는 상태라면
	{
		trail = h->list[con2];
		if (trail->key > con1)// 들어가고자하는 vertex가 가장 처음에 삽입되어야한다면
		{
			vertex1->link = trail; // trail을 이용하여 인접리스트에 바로 연결해주기
			h->list[con2] = vertex1;
		}

		else // vertex 삽입 위치 찾기(번호가 작은 vertex부터)
		{
			while (trail->key < con1) // 해당 vertex가 들어갈 위치 찾기
			{
				if (trail->link == NULL || trail->link->key > con1) // 가장 마지막에 삽입되어야하거나 위치를 찾았다면
					break; // 반복문 탈출
				trail = trail->link;
			}
			vertex1->link = trail->link; // 해당 위치에 연결
			trail->link = vertex1; // 앞 뒤 노드와 연결시켜주기
		}
	}
	listNode* vertex2 = (listNode*)malloc(sizeof(listNode)); // 두번째 삽입 vertex도 동일한 과정을 거침
	vertex2->key = con2; // 공간 할당 후, 데이터 삽입
	vertex2->link = NULL;

	if (h->list[con1] == NULL) // 해당하는 인접 리스트가 아무것도 가리키고 있지 않으면,
	{
		h->list[con1] = vertex2; // 바로 생성 vertex를 가리킴
	}
	else // 해당 인접리스트가 무언가를 가리키고 있는 상태라면
	{
		trail2 = h->list[con1];

		if (trail2->key > con2) // 들어가고자하는 vertex가 가장 처음에 삽입되어야한다면
		{
			vertex2->link = trail2;
			h->list[con1] = vertex2; // trail을 이용하여 인접리스트에 바로 연결해주기
			return;
		}

		else // vertex 삽입 위치 찾기(번호가 작은 vertex부터 탐색되어야함)
		{
			while (trail2->key < con2) // 해당 vertex가 들어갈 위치 찾기
			{
				if (trail2->link == NULL || trail2->link->key > con2) // 가장 마지막에 삽입되어야하거나 위치를 찾았다면
					break;
				trail2 = trail2->link;
			}
			vertex2->link = trail2->link; // 해당 위치에 연결
			trail2->link = vertex2;  // 앞 뒤 노드와 연결시켜주기
		}
	}return;
}

void printgraph(graph* h) // 그래프 상황 출력
{
	listNode* prev;
	printf("\n--PRINT--\n");
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		if (h->ident[i] == 1) // 삽입되어있는 vertex들만 출력
		{
			printf("Adjacent list of %d vertices : ", i);
			if (h->list[i] == NULL) // 해당 인접리스트가 아무것도 가리키고 있지 않다면,
			{
				printf("\n");
				continue;
			}
			prev = h->list[i]; // prev 포인터를 이용하여, 배열의 값 차례대로 출력
			while (prev != NULL)
			{
				printf("%d   ", prev->key);
				prev = prev->link;
			}
			printf("\n");
		}
	}return;
}

void dfs(graph* h, int key) // 깊이 우선 탐색_ 시작 정점을 key값으로 받음
{

	if (h->ident[key] != 1) // 입력된 vertex의 존재 확인
	{
		printf("vertex is not exist\n");
		return;
	}
	visited[key] = TRUE; // 방문 flag(마크) 찍기
	listNode* p = NULL;
	printf("%5d", key); // 해당 데이터 출력

	for (p = h->list[key]; p; p = p->link) // 해당노드의 다음 노드들과 차례로 연결
	{
		if ((visited[p->key]) != TRUE) // 해당 노드를 방문하지 않았으면
			dfs(h, p->key); // 방문하지 않은 노드를 인자로 하여 dfs 함수를 호출
	}
	front = rear = NULL;
}

void bfs(graph* h, int key) // 너비 우선 탐색-시작 정점을 key값으로 받음
{
	if (h->ident[key] != 1) // vertex의 존재확인
	{
		printf("vertex is not exist\n");
		return;
	}
	listNode* ptr = NULL;

	printf("%5d", key); // 데이터 출력
	visited[key] = TRUE; // 방문 확인

	enQueue(key); // 큐에 삽입

	while (front != rear) 
	{
		key = deQueue(); // 큐에서 pop해오기
		for (ptr = h->list[key]; ptr; ptr = ptr->link) // 해당노드의 다음 노드들과 차례로 연결
			if (!(visited[ptr->key])) // 노드를 방문하지않았으면
			{
				printf("%5d", ptr->key); // 데이터 출력
				enQueue(ptr->key); // 큐에 데이터 삽입
				visited[ptr->key] = TRUE; // 방문 플래그 찍기
			}
	} return;
}

listNode* deQueue() // 너비 우선 탐색에 필요-데이터 삭제
{
	if (front == rear)
	{
		printf("\nQueue is empty!\n");
		return NULL;
	}
	front = (front + 1) % MAX_VERTEX; // front 값을 옮겨주어서 없는 데이터 취급
	return queue[front];
}

void enQueue(listNode* aNode) // 너비 우선 탐색에 필요-데이터 삽입
{
	rear = (rear + 1) % MAX_VERTEX;
	if (front == rear) {
		printf("Queue is full\n");
		return;
	} queue[rear] = aNode;
}

void freegraph(graph* h) // 그래프 공간 해제
{
	listNode* k = NULL;
	listNode* prev = NULL;
	for (int i = 0; i < MAX_VERTEX; i++) // prev 포인터를 이용하여 인접리스트를 하나하나 돌면서 메모리 해제
	{
		k = h->list[i]; 
		while (k != NULL)
		{
			prev = k;
			k = k->link;
			free(prev);
		}
	}
}
