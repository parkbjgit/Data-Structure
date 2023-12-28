#include <stdio.h>
#include <stdlib.h>
void main()
{
printf("---------ParkBeomJun---------\n");
int list[5];                                        //5개를 저장하는 list배열선언
int *plist[5] = {NULL,};                           //포인터배열 plist 선언+초기화
plist[0] = (int *)malloc(sizeof(int));             //plist에 정수자료형 동적할당
list[0] = 1;                                       
list[1] = 100;
*plist[0] = 200;                                     //plist[0]이 가리키는 곳에 200
printf("value of list[0] = %d\n", list[0]);          //list[0]의 값 1
printf("address of list[0] = %p\n", &list[0]);        //list[0]의 주소값
printf("value of list = %p\n", list);                 //list[0]의 주소값
printf("address of list (&list) = %p\n", &list);      //list[0]의 주소값
printf("----------------------------------------\n\n");
printf("value of list[1] = %d\n", list[1]);          //list[1]의 값 100
printf("address of list[1] = %p\n", &list[1]);       //list[1]의 주소
printf("value of *(list+1) = %d\n", *(list + 1));    //list[1]의 값 100
printf("address of list+1 = %p\n", list+1);          //list[1]의 주소
printf("----------------------------------------\n\n");
printf("value of *plist[0] = %d\n", *plist[0]);     //plist[0]이 가리키는 곳의 값 200
printf("&plist[0] = %p\n", &plist[0]);              //plist[0]의 주소
printf("&plist = %p\n", &plist);                    //plist[0]의 주소
printf("plist = %p\n", plist);                      //plist[0]의 주소
printf("plist[0] = %p\n", plist[0]);                //plist[0]에 들어있는 주소값
printf("plist[1] = %p\n", plist[1]);               //아직 값이 할당되지않아 Null
printf("plist[2] = %p\n", plist[2]);               //아직 값이 할당되지않아 Null
printf("plist[3] = %p\n", plist[3]);               //아직 값이 할당되지않아 Null
printf("plist[4] = %p\n", plist[4]);               //아직 값이 할당되지않아 Null
free(plist[0]);                                    //plist 동적할당 해제
}