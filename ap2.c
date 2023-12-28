#include <stdio.h>
#include <stdlib.h>
void main()
{
printf("---------ParkBeomJun---------\n");
int list[5];                                   //배열 list 선언
int *plist[5];                                 //포인터배열 plist 선언
list[0] = 10;
list[1] = 11;
plist[0] = (int*)malloc(sizeof(int));             //plist에 정수형 동적할당
printf("list[0] \t= %d\n", list[0]);              //list[0]의 값
printf("address of list \t= %p\n", list);          //list[0]의 주소
printf("address of list[0] \t= %p\n", &list[0]);   //list[0]의 주소
printf("address of list + 0 \t= %p\n", list+0);    //list 자체는 주소를 의미
printf("address of list + 1 \t= %p\n", list+1);    //list[1]의 주소  4bytle만큼 증가
printf("address of list + 2 \t= %p\n", list+2);    //list[2]의 주소  4bytle만큼 증가
printf("address of list + 3 \t= %p\n", list+3);    //list[3]의 주소  4bytle만큼 증가
printf("address of list + 4 \t= %p\n", list+4);    //list[4]의 주소  4bytle만큼 증가
printf("address of list[4] \t= %p\n", &list[4]);   //list[4]의 주소
free(plist[0]);                                    //plsit 동적할당 해제
}