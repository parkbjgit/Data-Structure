#include <stdio.h>
#include <stdlib.h>

typedef struct node {//트리구조를 구현할 구조체
	int key; 
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

int main()
{
	printf("---------------------2021041022   박범준------------------------\n");
	char command;
	int key;
	Node* head = NULL;  //포인터들을 초기화
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n"); 
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);			//트리구조 초기화
			break;
		case 'q': case 'Q':
			freeBST(head);					//동적할당을 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);				//키를 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);		//리프노드를 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);     //iteratively하게 찾아서 ptr에 넣기
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);   //노드를 찾고 그 주소를 출력
			else
				printf("\n Cannot find the node [%d]\n", key);			//없다면 노드를 찾을수 없음 
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);				//recursively하게 찾아 ptr에 넣기
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);	//노드를 찾고 그 주소를 출력
			else
				printf("\n Cannot find the node [%d]\n", key);		//없다면 노드를 찾을수 없음
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);		//inorder 방식으로 트리출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);		//preorder 방식으로 트리출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left);		//postorder 방식으로 트리출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {
	if(*h != NULL)
		freeBST(*h); 		//트리가 비어있지않으면 모든 할당된 노드를 할당 해제

	*h = (Node*)malloc(sizeof(Node));		//head노드를 Node의 크기만큼 동적할당+초기화
	(*h)->left = NULL;			/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);		//ptr값이 존재한다면 inorder방식으로 (left,right)키들을 출력
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);			//ptr값이 존재한다면 preorder방식으로 (left,right)키들을 출력
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);		//ptr값이 존재한다면 postorder방식으로 (left,right)키들을 출력
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	//새로운 노드를 동적할당하고 초기화
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {   	//head->left가 NULL이라면 newNode를 넣기
		head->left = newNode;
		return 1;
	}
	/* head->left is the root */
	Node* ptr = head->left;			//ptr에 left를 넣기

	Node* parentNode = NULL;		//부모노드 NULL로 초기화
	while(ptr != NULL) {			//ptr이 NULL이 아니라면 

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;		//ptr->key가 key와 같다면 1을 리턴
		parentNode = ptr;				//ptr을 이용해 부모노드를 따라간다

		if(ptr->key < key)   	 //key값을 비교해서 현재 key가 입력key가 더 크다면 새로운 노드를 right의 서브트리에 삽입
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if(parentNode->key > key)		//부모노드의 키와 키를 비교하여 left,right애 넣을지 결정
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");		//head가 NULL이라면 삭제할 것이 없음
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");		//left가 NULL이라면 삭제할 것이 없음
		return -1;
	}
	/* head->left is the root */
	Node* ptr = head->left;

	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {			//ptr이 NULL이 아니라면 

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {		//ptr의 left,right가 둘다 NULL이라면 

				if(parentNode == head)				//부모노드가 head이고 head->left가 NULL이라면
					head->left = NULL;

				if(parentNode->left == ptr)		//부모노드의 left와 right를 NULL 초기화
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);				//ptr 동적할당해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);		//아닌 경우 리프노드가 아니다 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		if(ptr->key < key)		//ptr->key와 key를 비교하여 left,right일지 결정
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	printf("Cannot find the node for key [%d]\n ", key);		//아닌 경우 키를 찾을수 없음

	return 1;
}

Node* searchRecursive(Node* ptr, int key)	//ptr을 통해 recursive하게 찾는 방법
{
	if(ptr == NULL)				//ptr이 NULL이라면 NULL반환
		return NULL;
 
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key); //ptr->key와 key를 비교해 left,right를 반환
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;
}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;    

	while(ptr != NULL) 			//ptr이 NULL이 아니라면 반복
	{
		if(ptr->key == key)    //ptr->key == key라면 ptr반환 
			return ptr;

		if(ptr->key < key)  	//ptr->key와 key를 비교하여 left,right 반환
		ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);   //recursive하게 ptr을 해제
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	if(head->left == head)		//head->left와 head가 같으면 head 해제
	{
		free(head);
		return 1;
	}
	Node* p = head->left; 		//p,head를 해제
	freeNode(p);
	free(head);
	return 1;
}
