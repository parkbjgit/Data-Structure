#include<stdio.h>
#include<stdlib.h>
void main()
{
printf("---------ParkBeomJun---------\n");
int **x;                                    //이중포인터 변수x 선언
printf("sizeof(x) = %lu\n", sizeof(x));     //x의 크기=4->포인터변수는 4(32bit로 컴파일하므로)
printf("sizeof(*x) = %lu\n", sizeof(*x));   //*x의 크기=4->포인터변수는 4(32bit로 컴파일하므로)
printf("sizeof(**x) = %lu\n", sizeof(**x)); //**x의 크기=4->int형 이중포인터이므로 4를 출력