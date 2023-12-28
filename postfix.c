#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_STACK_SIZE 10                          //변수값 고정
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{                                       //열거형을 typedef로 정의
	lparen = 0,  /* ( 왼쪽 괄호 */                  
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];        //중위표현 배열
char postfixExp[MAX_EXPRESSION_SIZE];     //후위표현배열
char postfixStack[MAX_STACK_SIZE];         //후위표현 스택 
int evalStack[MAX_STACK_SIZE];            //스택안의 값들
int postfixStackTop = -1;               //초기값
int evalStackTop = -1;
int evalResult = 0;                     //결과값의 초기값

void postfixPush(char x);                //함수들 선언
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);          
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	printf("---------------Park Beom Jun 2021041022-------------------------\n");
	char command;                                       //명령어 
	do{
		printf("----------------------------------------------------------------\n");        //메뉴얼 출력
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);                      //명령어 입력받기
		switch(command) {
		case 'i': case 'I':                         //각각의 명령어에 대한 실행
			getInfix();                              //중위 수식연산 입력받기
			break;
		case 'p': case 'P':
			toPostfix();                           //후위연산으로 변환
			break;
		case 'e': case 'E':
			evaluation();                         //계산
			break;
		case 'd': case 'D':
			debug();                            //디버그하기
			break;
		case 'r': case 'R':
			reset();                          //초기화
			break;
		case 'q': case 'Q':                      
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');                      //q가 입력될 때까지
	return 1;
}

void postfixPush(char x){
    postfixStack[++postfixStackTop] = x;       //후위연산 스택에 문자x를 넣기(전위증가)
}

char postfixPop(){
	char x;
    if(postfixStackTop == -1)                     //후위연산스택의 top이 -1이라면
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];      //아니라면 후위연산스택의 top의 값을 x에 넣기(후위감소)
    }
    return x;}

void evalPush(int x){
    evalStack[++evalStackTop] = x;                //x를 evalstack에 push(전위증가)
}

int evalPop(){
    if(evalStackTop == -1)                         //evalstacktop이 -1이라면
        return -1;
    else
        return evalStack[evalStackTop--];         //evalstack의 top값을 pop(후위감소)
}

void getInfix(){
    printf("Type the expression >>> ");         //infix expression을 입력받기
    scanf("%s",infixExp);                       //infixexp에 저장
}

precedence getToken(char symbol)              //열거형으로 토큰 가져오기
{
	switch(symbol) {                          
	case '(' : return lparen;                //case 별로 연산자 리턴
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)              //열거형의 우선순위에 따라 가져오기
{
	return getToken(x);
}

void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);           //c의 문자 한개를 postfixExp에 복사
	else
		strncat(postfixExp, c, 1);            //postfixExp와 c의 문자열을 이어 붙임
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')                        //infixExp가 없을때까지 실행
	{
		if(getPriority(*exp) == operand)            //exp가 연산자라면
		{
			x = *exp;                                 //x에 연산자 대입
        	charCat(&x);                             
		}
        else if(getPriority(*exp) == lparen) {          //exp가 왼쪽 괄호라면

        	postfixPush(*exp);                         //exp를 push
        }
        else if(getPriority(*exp) == rparen)                //오른쪽괄호라면
        {
        	while((x = postfixPop()) != '(') {            //x가 '('가 아니라면 게속 실행
        		charCat(&x);                              //x를 한개씩 복사
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))   
            {                                     //우선순위가 postfixstack이 exp보다 크거나 같으면 
            	x = postfixPop();                //x에 pop한 값을 대입
            	charCat(&x);                     //x 하나씩 복사
            }
            postfixPush(*exp);                    //exp push
        }
        exp++;            //exp 후위증가연산
	}

    while(postfixStackTop != -1)                     //postfixstacktop이 -1이 아니면
    {
    	x = postfixPop();                          //pop한 값을 x에 대입
    	charCat(&x);                               //x하나씩 복사
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);               //중위표기 수식 출력
	printf("postExp =  %s\n", postfixExp);              //후위표기 수식 출력
	printf("eval result = %d\n", evalResult);           //계산결과값 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)            //postfixstack에 있는 문자를 모두 출력
		printf("%c  ", postfixStack[i]);
	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';                          //infix와 postfix 초기화
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)         //스택의 사이즈만큼 postfixstack 초기화
		postfixStack[i] = '\0';                    
         
	postfixStackTop = -1;                         //-1로 초기화
	evalStackTop = -1;
	evalResult = 0;                    //결과값 0 초기화
}
void evaluation()
{
	int opr1, opr2, i;               //정수형 변수 선언

	int length = strlen(postfixExp);      //수식의 길이만큼  length에 대입
	char symbol;                          
	evalStackTop = -1;                          

	for(i = 0; i < length; i++)               //수식의 길이만큼 실행
	{
		symbol = postfixExp[i];                       //수식에서 하나씩 symbol에 대입
		if(getToken(symbol) == operand) {             //symbol이 피연산자라면
			evalPush(symbol - '0');                   //아스키코드값으로 계산
		}
		else {
			opr2 = evalPop();                           //피연산자를 pop
			opr1 = evalPop();
			switch(getToken(symbol)) {                   //symbol에 따라 + - * / 연산하여 push
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop();                              //결과값을 pop
}
