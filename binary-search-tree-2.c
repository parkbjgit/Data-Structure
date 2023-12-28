#include <stdio.h>
#include <stdlib.h>

typedef struct node {     //트리구조의 구조체를 선언
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];       //스택의 배열을 선언
int top = -1;					//top 초기화

Node* pop();					//pop과 push함수 선언
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];		//queue배열 선언+front,rear 초기화
int front = -1;
int rear = -1;

Node* deQueue();				//deQueue,enQueue 함수 선언
void enQueue(Node* aNode);

int initializeBST(Node** h);		//BST 초기화

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

void printStack();

int main()
{
	char command;
	int key;
	Node* head = NULL;
    printf("-------------2021041022-------ParkBeomJun-----------------------\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");	//명령어들의 메뉴를 출력
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);			 //BST 초기화(head의 주소를 받는다)
			break;
		case 'q': case 'Q':
			freeBST(head);					//BST 동적할당 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);				//key를 삽입
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");			//key 삭제
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);	//recursiveInorder 방식으로 출력
			break;
		case 't': case 'T':
			iterativeInorder(head->left);	//iterativeInorder 방식으로 출력
			break;

		case 'l': case 'L':
			levelOrder(head->left);			//levelOrder 방식으로 출력
			break;

		case 'p': case 'P':
			printStack();			//stack 출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	if(*h != NULL)  //트리가 비어있지 않다면 트리의 동적할당을 해제
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); 	//h에 동적할당하고 left,right,key 초기화
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;				//top,front,rear 초기화
	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);	//recursive하게 left부터 right로 key를 출력
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)
{
	for(;;) //이중 for문 사용 
	{
		for(; node; node = node->left) 		//stack을 이용해 left부터 하나씩 pop
			push(node);
		node = pop();

		if(!node) break;             	//node가 존재하지 않으면 break
		printf(" [%d] ", node->key);    //key를 출력
		node = node->right;			//right로 이동
	}
}

void levelOrder(Node* ptr)
{
	if(!ptr) return; /* empty tree */
	enQueue(ptr);	//큐에 추가

	for(;;)
	{
		ptr = deQueue(); //큐에서 삭제
		if(ptr) {
			printf(" [%d] ", ptr->key); 

			if(ptr->left)             //left나 right에 큐 추가
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));    //newNode를 동적할당+key,left,right 초기화
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {			//left가 비어있으면 newNode 추가
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL; 	//부모노드 NULL 초기화
	while(ptr != NULL) {		//ptr이 NULL이 아닐때까지

		if(ptr->key == key) return 1; /* if there is a node for the key, then just return */

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		if(ptr->key < key)    //key의 크기를 비교하여 입력받은 key가 더 크다면 서브트리의 right에 삽입
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if(parentNode->key > key)       //부모노드의 key와 key를 비교하여 left나 righ에 newNode 연결
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n"); //head가 NULL이라면 삭제할 것이 없음
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n"); //left가 NULL이어도 삭제할 것이 없음
		return -1;
	}
	Node* root = head->left;	 /* head->left is the root */

	Node* parent = NULL; 	//parent를 NULL 초기화
	Node* ptr = root; 		//root를 ptr에 넣기

	while((ptr != NULL)&&(ptr->key != key)) { //ptr이 NULL이 아니고 ptr->key과 key가 같지않다면
		if(ptr->key != key) {
			parent = ptr;	/* save the parent */

			if(ptr->key > key)
				ptr = ptr->left;  //key의 크기를 비교하여 left,right 결정
			else
				ptr = ptr->right;
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key); 	//ptr이 NuLL이면 키가 존재하지않음
		return -1;
	}
    //case 1: 삭제돼야할 노드가 리프노드라면
	if(ptr->left == NULL && ptr->right == NULL) 
	{
		if(parent != NULL) { 	/* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)  	//left와 right를 초기화
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			head->left = NULL; 	//parent가 NULL인것은 삭제되어야할 노드가 root
		}

		free(ptr);	//동적할당해제
		return 1;
	}

	 //case 2: 삭제돼야할 노드가 하나의 자식이 있을시
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)   //자식을 ptr->left나 right로 초기화
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)	//부모가 null이 아니라면
		{
			if(parent->left == ptr)
				parent->left = child; //부모의 left나 right에 child 넣기
			else
				parent->right = child;
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);		//동적할당해제
		return 1;
	}

	 /* case 3:  node가 두 자식을 가진다면 왼쪽에서 가장 큰 자식이나 오른쪽에서 가장 작은 자식을 선택
	 */
	Node* candidate;
	parent = ptr;

	candidate = ptr->right; 	//candidate에 right 대입

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)  
	{
		parent = candidate;             //right에서 가장 작은 노드
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;  //parent의 right나 left를 parent->right와 candidate비교로 선택
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //삭제대신에 key만 바꿔줌

	free(candidate);		//동적할당해제
	return 1;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);    //left,right,ptr 동적할당해제
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	if(head->left == head)		//head->left와 head가 같다면 head할당 해제
	{
		free(head);
		return 1;
	}

	Node* p = head->left;   	//p에 left 넣어주기

	freeNode(p);    			//할당해제
	free(head);					//할당해제
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL; 	//top이 음수면 NULL 리턴, 아니라면 stack[top--] 리턴
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top] = aNode; 		//stack에서 aNode push
}

void printStack()
{
	int i = 0;
	printf("--- stack ---\n");					//stack을 top까지 key 출력
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;	//큐 삭제시 front+1
	return queue[front];
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;		//큐에 하나씩 추가시 rear+1
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}
	queue[rear] = aNode;  //새로운 큐
}

