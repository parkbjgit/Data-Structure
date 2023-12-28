#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;                 //입력받을 키와 노드를 링크할 포인터변수 llink rlink 구조체
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {       
	struct Node* first;     //구조체 Head와 포인터변수 first
}headNode; 

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);                 //이중포인터변수 h를 매개 초기화함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);                    

int insertNode(headNode* h, int key);        //크기를 비교해 key를 삽입
int insertLast(headNode* h, int key);        //추가 노드에 key를 추가
int insertFirst(headNode* h, int key);       //처음노드에 key 삽입
int deleteNode(headNode* h, int key);        //삭제할 key를 입력받아 노드삭제
int deleteLast(headNode* h);                 //마지막 노드를 삭제
int deleteFirst(headNode* h);                //처음 노드를 삭제
int invertList(headNode* h);                 //노드를 역순으로 전환

void printList(headNode* h);                 //노드 출력


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
    printf("--------------------2021041022 ParkBeomJun----------------------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);         //더블포인터를 이용하므로 headnode의 주소를 매개
			break;
		case 'p': case 'P':
			printList(headnode);           //리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);     
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);         //해제함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if(*h != NULL)
		freeList(*h); /* headNode가 NULL이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */

	*h = (headNode*)malloc(sizeof(headNode)); /* headNode에 대한 메모리를 할당하여 리턴 */
	(*h)->first = NULL;              //first를 null초기화
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;       //prev를 null 초기화
	while(p != NULL) {           //p가 null이 아니라면 first인 p를 prev에 넣고 rlink를 p에 넣고 
		prev = p;                //prev를 동적할당해제함, h도 동적할당해제*/
		p = p->rlink;             
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;                       //포인터변수 p를 선언

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");     //h가 null이면 출력할 것이 없음
		return;
	}

	p = h->first;                    //first를 p에 넣음

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);      //rlink를 이용하여 순차적으로 출력
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);              //몇개의 노드가 출력인지 확인
}

int insertLast(headNode* h, int key) {              //리스트에 key에 대한 노드를 추가

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode크기만큼 동적할당
	node->key = key;           //key를 Node의 key에, rlink와 llink를 null로 초기화
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)           //first가 Null이라면 node를 first에 넣어줌
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;        //그리고 위의 first를 n에 넣어줌
	while(n->rlink != NULL) {      //rlink가 null이 아닐시 rlink를 n에 넣어준다(마지막 노드까지 가기위해)
		n = n->rlink;
	}
	n->rlink = node;               //위의 반복문을 나오고 node를 rlink에 n을 llink에 넣는다
	node->llink = n;
	return 0;
}

int deleteLast(headNode* h) {                //리스트의 마지막 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");         //first가 null이라면 삭제할 것이 없음
		return 0;
	}

	listNode* n = h->first;                  //n에 first, trail을 null 로 초기화
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;                 //rlink가 null이라면 first에 null을 넣고 n동적할당해제
		free(n);
		return 0;
	}
	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {         //rlink가 null이 되기전까지 trail에 n을 rlink를 n에 넣어줌
		trail = n;
		n = n->rlink;
	}
	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;            
	free(n);
	return 0;
}

int insertFirst(headNode* h, int key) {                 //리스트 처음에 key에 대한 노드하나를 추가

	listNode* node = (listNode*)malloc(sizeof(listNode));      //listNode 크기만큼 동적할당,key와 rlink,rlink를 준비
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)              //first가 null이라면 node를 first에 넣어줌
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;         //first를 rlink에, llink를 null로 초기화
	node->llink = NULL;

	listNode *p = h->first;         //새로운 p를 선언하고 p에 node의 값들을 입력시킴
	p->llink = node;
	h->first = node;

	return 0;
}

int deleteFirst(headNode* h) {            //리스트의 첫번째 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");         //first가 null이라면 삭제할 것이 없음
		return 0;
	}
	listNode* n = h->first;              //새로운 n에 first, first에는 rlink를 넣어줌
	h->first = n->rlink;

	free(n);
	return 0;
}

int invertList(headNode* h) {               //리스트의 링크들을 역순으로 재배치

	if(h->first == NULL) {
		printf("nothing to invert...\n");            //first가 null이라면 전환할 것이 없음
		return 0;
	}
	listNode *n = h->first;            //n에는 first를, trail과 middle은 null로 초기화
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;               //역순으로 전환하기위해 n이 null이 되기전까지 실행
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
	h->first = middle;              //first에 middle을 넣어줌
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));   
	node->key = key;
	node->llink = node->rlink = NULL;             //node의 rlink와 llink를 준비

	if (h->first == NULL)
	{
		h->first = node;           //first가 null 이라면 node를 first에
		return 0;
	}

	listNode* n = h->first;             //n에 first를 넣어줌

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {               //n이 null이 되기전까지
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);         //n이 first와 같다면 처음 노드에 추가함수 
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;            //node와 n을 통해 삽입위치를 지정
				n->llink->rlink = node;
			}
			return 0;
		}
		n = n->rlink;          //rlink를 n에 넣어줌
	}
	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

int deleteNode(headNode* h, int key) {           //리스트에서 key에 대한 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");         //first가 null이라면 삭제할 것이 없음
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 처음노드 삭제*/
				deleteFirst(h);         
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 마지막 노드 삭제 */
				deleteLast(h);            
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;       //rlink와 llink를 통해 삭제
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}
		n = n->rlink;
	}
	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


