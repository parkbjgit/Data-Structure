#include <stdio.h>
void print1 (int *ptr, int rows);       //print1 함수 선언
int main()
{
printf("---------ParkBeomJun---------\n");
int one[] = {0, 1, 2, 3, 4};           //배열 one선언
printf("one = %p\n", one);             //one은 그 자체로 주소이므로 one[0]의 주소
printf("&one = %p\n", &one);           //one[0]의 주소
printf("&one[0] = %p\n", &one[0]);     //one[0]의 주소
printf("\n");
print1(&one[0], 5);                    //배열one을 매개로 한 print1 함수 이용
return 0;
}
void print1 (int *ptr, int rows)       //print1 함수 정의
{/* print out a one-dimensional array using a pointer */
int i;
printf ("Address \t Contents\n");
for (i = 0; i < rows; i++)                  //0~row-1까지 반복
printf("%p \t %5d\n", ptr + i, *(ptr + i)); //(ptr+i)에 들어있는 주소값과 (ptr+i)이 가리키는 값 one[0~4]출력
printf("\n");
}