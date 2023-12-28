#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4                     //최대 큐사이즈를 4로 정의

typedef char element;                        
typedef struct {                            //구조체를 QueueType으로 별칭
	element queue[MAX_QUEUE_SIZE];          //구조체 안에 문자 배열 큐
	int front, rear;              //새로운 값이 삽입되는 끝rear와 삭제되는 끝front 
}QueueType;

QueueType *createQueue();                          //함수 선언
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();     //큐를 생성한다
	element data;
    printf("--------------2021041022 Park Beom Jun---------------");
	char command;                                                       //명령어 변수
	do{                         //q,Q가 입력될 때까지 계속 실행
		printf("\n-----------------------------------------------------\n"); //메뉴얼
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command); //명령어를 입력받는다

		switch(command) {
		case 'i': case 'I':
			data = getElement();        //데이터를 추가
			enQueue(cQ, data);          //큐에 데이터를 추가
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);          //큐에서 데이터를 삭제
			break;
		case 'p': case 'P':
			printQ(cQ);                 //큐를 출력하기
			break;
		case 'b': case 'B':
			debugQ(cQ);                 //디버깅하기
			break;
		case 'q': case 'Q':
			break;
		default:                        //다른 값이 입력될 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;               //구조체 포인터 변수 cQ
	cQ = (QueueType *)malloc(sizeof(QueueType));    //cQ를 구조체크기만큼 동적 할당
	cQ->front = 0;                                  //front와 rear을 0으로 초기화
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)                
{
    if(cQ == NULL) return 1;               //만약 cQ가 NULL이라면 1리턴
    free(cQ);                              //cQ의 동적할당 해제
    return 1;
}

element getElement()                   //큐에 원소를 추가받는 함수
{
	element item;                     
	printf("Input element = ");
	scanf(" %c", &item);                //큐에 넣을 문자를 입력
	return item;
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){                  //만약 front와 rear가 같다면
		printf("Circular Queue is empty!");      //순환큐가 비었다고 출력
		return 1;
	}
	else return 0;                              //아니라면 0을 리턴
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {    //만약 rear+1을 큐사이즈로 나누었을 때 
		printf(" Circular Queue is full!");             //나머지가 front와 같다면 큐가 가득 찼다고 출력
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;                             //만약 cQ가 가득 차있다면
	else {                                              //가득 차지 않았다면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //rear는 그 다음 index가 rear가 된다
		cQ->queue[cQ->rear] = item;                      //입력받은 원소를 cQ의 rear에 넣어줌
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;                          //cQ가 비어있다면
	else {                                          
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;   //front는 그 다음 index가 front가 된다
		*item = cQ->queue[cQ->front];                 //item에 front값을 넣기
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;          //first는 front+1을 큐사이즈로 나눈 나머지 값
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;            //last는 rear+1을 큐사이즈로 나눈 나머지 값

	printf("Circular Queue : [");                    //큐를 출력

	i = first;              
	while(i != last){                               //first와 last가 같지않다면
		printf("%3c", cQ->queue[i]);                //큐를 출력
		i = (i+1)%MAX_QUEUE_SIZE;                   //큐 배열의 다음 원소

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)                         //큐를 확인하는 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {                       //front가 i와 같다면
			printf("  [%d] = front\n", i);         //어떤 i가 front인지를 출력
			continue;                              //이어서
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);   //큐의 내용 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);        //front와 rear를 출력
}
