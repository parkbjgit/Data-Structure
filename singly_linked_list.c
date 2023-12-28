#include<stdio.h>
#include<stdlib.h>

typedef struct Node {            //구조체 Node를 key와 포인터 link로 구성
	int key;
	struct Node* link;
} listNode;                      //구조체 변수 listNode

typedef struct Head {            //구조체 Head 포인터 first로 구성
	struct Node* first;        
}headNode;                       //변수 headNode

/* 함수 리스트 */
headNode* initialize(headNode* h);            //h 초기화
int freeList(headNode* h);                    //동적할당해제
int insertFirst(headNode* h, int key);       //첫번째 노드에 key 삽입
int insertNode(headNode* h, int key);        //key값보다 큰 값의 Node앞에 key삽입
int insertLast(headNode* h, int key);        //마지막 노드에 key 삽입
int deleteFirst(headNode* h);                //첫번째 노드 key 삭제
int deleteNode(headNode* h, int key);        //key 값을 입력받아 그 Node 삭제
int deleteLast(headNode* h);                 //마지막 노드의 key 값을 삭제
int invertList(headNode* h);                 //리스트의 링크를 역순으로 바꾸기

void printList(headNode* h);                 //리스트 출력

int main()
{
	char command;                        //메뉴얼 명령어
	int key;                            //삽입할 key 값
	headNode* headnode=NULL;             //초기화
    printf("------------------2021041022  박범준-------------------------");
	do{
		printf("----------------------------------------------------------------\n");     //메뉴얼 출력
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);      //명령어 입력받기

		switch(command) {
		case 'z': case 'Z':                         //command 별로 경우 나누어서 실행
			headnode = initialize(headnode);        //headNode 초기화
			break;
		case 'p': case 'P':
			printList(headnode);                    //리스트출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);                     //key값보다 큰 값의 Node앞에 key삽입
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");                 //key값을 입력받아 리스트에서 삭제
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");                 //마지막 노드에 key 삽입
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':                       //마지막 노드의 key 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");                //첫번째 노드에 key 삽입
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);               //첫번째 노드의 key 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);                //리스트의 순서를 역순으로 변환
			break;
		case 'q': case 'Q':
			freeList(headnode);                  //동적할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");      //이외의 값은 "집중"출력
			break;
		}

	}while(command != 'q' && command != 'Q');          //q 입력시 종료

	return 1;
}

headNode* initialize(headNode* h) {                    //headNode 초기화 함수 정의
 
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));      //headNode 사이즈만큼 동적할당 
	temp->first = NULL;                             //temp의 first를 NULL 초기화
	return temp;                               
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;           //first를 p에 넣기

	listNode* prev = NULL;           //prev를 NULL로 초기화해주고
	while(p != NULL) {             //p가 NULL이 되기전까지
		prev = p;                   //prev에는 p를, p에는 p의 link를 넣어줌
		p = p->link;
		free(prev);             //동적할당 해제
	}
	free(h);                
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;                   //key를 node의 key에 넣어줌
	node->link = NULL;

	if (h->first == NULL)             //만약 first가 NULL이라면 
	{
		h->first = node;               //first가 node로 됨
		return 0;
	}

	listNode* n = h->first;           //구조체포인터 n에 first를 넣어줌 
	listNode* trail = h->first;        //trail에 first를 넣어줌
 
	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {        //n의 key가 key보다 크다면 
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {    //같다면 first가 node가 되고 link에 n을 넣어줌
				h->first = node;
				node->link = n;
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;    //node의 key에 key 넣기
	node->link = NULL;   //초기화

	if (h->first == NULL)  //first가 NULL이라면 first가 node가 됨
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {     //link가 NULL이 되기 전까지 n에 link 넣기
		n = n->link;          
	}
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;                   //node의 key에 key를 넣기 

	node->link = h->first;         //link에 first를 넣어주고 first가 node가 됨
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)       //first가 NULL이라면 삭제할 것이 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삭제할 위치를 찾는다 */
	while(n != NULL) {                 //n이 null이 되기전까지 
		if(n->key == key) {         //n의 key와 찾는 key가 같다면 
			if(n == h->first) {       //n과 h의 first가 같다면
				h->first = n->link;
			} else { 
				trail->link = n->link;
			}
			free(n);                  //메모리를 낭비하지않도록
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 key를 찾을 수 없음 출력*/
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)               //first가 NULL이라면 삭제할 것이 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;           //n에는 first를, trail에는 null을 넣어줌
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {          //link가 null이라면 first도 null이 됨
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { //link가 null이 아니기 전까지 trail에는 n을 n에는 link를 넣어줌
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;       
	free(n);              //동적 할당 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)    //만약 h의 first가 NULL이라면 "삭제할 것이 없다" 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;     //first를 n에 넣어주고

	h->first = n->link;     //first를 link로 교체
	free(n);                //n의 동적할당 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {                //first가 NULL이라면 교환할것이 없다
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){            //link들의 값들을 역순으로 바꿔줌
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;        //first에 middle을 넣어줌

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {                          //h가 NULL이라면 출력할 것이 없음
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {          //p가 NULL이 될때까지 index와 key 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);    //몇개가 리스트에 있는지 출력
}
