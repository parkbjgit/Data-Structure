#include<stdio.h>
#include<stdlib.h>       //헤더파일

typedef struct Node {
	int key;                 //구조체 선언
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);         //초기화함수
int freeList(listNode* h);            //동적할당해제
int insertLast(listNode* h, int key); //마지막 노드에 삽입
int deleteLast(listNode* h);          //마지막 노드 삭제
int insertFirst(listNode* h, int key);//첫번째 노드에 삽입
int deleteFirst(listNode* h);         //첫번재 노드 삭제
int invertList(listNode* h);          //리스트 역순으로 전환

int insertNode(listNode* h, int key); //노드 삽입
int deleteNode(listNode* h, int key); //노드 삭제
void printList(listNode* h);          //리스트 출력

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;    //포인터변수 선언+NULL로 초기화
    printf("-----------------------2021041022 ParkBeomJun-------------------\n");
	do{
		printf("----------------------------------------------------------------\n");      //메뉴얼 출력
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);    //초기화(이때 더블포인터로 받을 것이기 때문에 headnode의 주소로 매개한다)
			break;
		case 'p': case 'P':
			printList(headnode);      //리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);    //key를 입력받아 오름차순으로 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);   //key를 입력받아 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);      //마지막 노드에 key 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);        //마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);  //첫번지ㅐ 노드에 key 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);      //첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);        //리스트 역순으로 전환
			break;
		case 'q': case 'Q':
			freeList(headnode);         //동적할당해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

int initialize(listNode** h) {
	if(*h != NULL)     /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
		freeList(*h);
	*h = (listNode*)malloc(sizeof(listNode));   /* headNode에 대한 메모리를 할당하여 리턴 */
	(*h)->rlink = *h;                           //h의 rlink,llink,key값을 할당
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){
	if(h->rlink == h)         //rlink가 h와 같다면 h의 동적할당해제
	{
		free(h);
		return 1;
	}
	listNode* p = h->rlink;       //p에 rlink 넣기
	listNode* prev = NULL;        //prev를 null 초기화
	while(p != NULL && p != h) {    //p가 null,h와 같지않다면 동적할당해제
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");           //h가 null이라면 출력할 것이 없음
		return;
	}
	p = h->rlink;      //p에 rlink 넣기

	while(p != NULL && p != h) {             //p가 null도 아니고 h도 아니라면 
		printf("[ [%d]=%d ] ", i, p->key);   //리스트의 값들을 순차적으로 출력
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);        //item들이 몇개인지 출력

	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);     //llink,h,rlink 주소를 출력

	i = 0;            //i를 0으로 초기화
	p = h->rlink;     //p에 rlink를 넣어줌
	while(p != NULL && p != h) {                //p가 null,h가 아니라면 리스트의 노드들의 key와 llink,p,rlink의 주소를 순차적으로 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

int insertLast(listNode* h, int key) {        //list에 key에 대한 노드하나를 추가
	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));    //node에 동적할당하고 key,rlink,llink 초기화
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h)            /* 첫 노드로 삽입할 때의 h와 node의 rlink,llink 초기화 */
	{
		h->rlink = node;    
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}
	return 1;
}

int deleteLast(listNode* h) {     //list의 마지막 노드 삭제
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");       //llink가 h와 같거나 h가 null이라면 출력할 것이 없음
		return 1;
	}

	listNode* nodetoremove = h->llink;    //h의 llink를 삭제할 노드에 넣기

	/* 삭제할 노드의 rlink와 llink 정리 */
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove);     //nodetoremove 의 동적할당 해제

	return 1;
}

int insertFirst(listNode* h, int key) {                   //list 처음에 key에 대한 노드하나를 추가

	listNode* node = (listNode*)malloc(sizeof(listNode));  //node에 동적할당+nod의 key,rlink,llink를 초기화
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	node->rlink = h->rlink;              //첫번째노드에 넣어준 후 순환하기위한 link를 정리
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;

	return 1;
}

int deleteFirst(listNode* h) {      //list의 첫번째 노드 삭제

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");        //h가 null이거나 rlink와 h가 같다면 삭제할 것이 없음
		return 0;
	}

	listNode* nodetoremove = h->rlink;        //삭제할 노드에 rlink를 넣기
	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);              //동적할당 해제
	return 1;
}

int invertList(listNode* h) {          //리스트의 링크를 역순으로 재배치

	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");     //rlink가 h이거나 h가 null이라면 전환할 것이 없음 출력
		return 0;
	}
	listNode *n = h->rlink;          //역순으로 바꾸기위한 포인터변수들
	listNode *trail = h;
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){      //n이 null과 h가 아니라면 포인터변수들과 link 정리
		trail = middle;             //middle,trail 이용
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
	h->rlink = middle;              
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;         //새로운 노드를 생성+초기화

	if (h->rlink == h)
	{
		insertFirst(h, key);       //비어있었다면 insertFirst
		return 1;
	}
	listNode* n = h->rlink;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {        //n이 null과 h와 같지않다면 
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 순환적인 링크 정리*/
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}
		n = n->rlink;
	}
	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

int deleteNode(listNode* h, int key) {        //list에서 key에 대한 노드 삭제

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");            //rlink가 h와 같거나 h가 null이라면 삭제할 것이 없음 출력
		return 0;
	}
	listNode* n = h->rlink;          //n에 rlink 할당

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) {            /* 첫 노드째 노드 인경우 첫번째 노드를 삭제*/
				deleteFirst(h);
			} else if (n->rlink == h){     /* 마지막 노드인 경우 마지막 노드 삭제*/
				deleteLast(h);
			} else {                       /* 중간인 경우 순환적 링크 정리+동적할당 해제*/
				n->llink->rlink = n->rlink;  
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}
		n = n->rlink;
	}
	/* 찾지 못 한경우 키를 찾지 못함 출력*/
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


