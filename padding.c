#include <stdio.h>
struct student {
char lastName[13]; /* 13 bytes */            //student 구조체 선언
int studentId; /* 4 bytes */
short grade; /* 2 bytes */
};
int main()
{
printf("---------ParkBeomJun---------\n");
struct student pst;                                        //student 구조체 변수 pst
printf("size of student = %ld\n", sizeof(struct student)); //student 구조체의 데이터크기                                                  
printf("size of int = %ld\n", sizeof(int));                //int형의 데이터크기
printf("size of short = %ld\n", sizeof(short));            //short형의 데이터크기
return 0;                                  //원래라면 19바이트겠지만 int기준으로 4의배수로 계산 (16+4+4)
}