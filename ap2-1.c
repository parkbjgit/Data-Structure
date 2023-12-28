#include <stdio.h>
#define MAX_SIZE 100                       //MAX_SIZE=100
float sum(float [], int);                  //sum 함수 선언
float input[MAX_SIZE], answer;             //input 함수 선언
int i;
void main(void)
{
printf("---------ParkBeomJun---------\n");
for(i=0; i < MAX_SIZE; i++)                  //i=0~99까지 반복
input[i] = i;                                //input[i]값은 i
/* for checking call by reference */
printf("address of input = %p\n", input);    //input[0]의 주소
answer = sum(input, MAX_SIZE);               //answer에 sum함수결과 값을 대입
printf("The sum is: %f\n", answer);          //0~99까지의 합 answer 출력
}
float sum(float list[], int n)                //sum 함수 정의
{
printf("value of list = %p\n", list);         //list[0]에 들어있는 주소값
printf("address of list = %p\n\n", &list);    //list[0]의 주소
float tempsum = 0;                            //tempsum=0 초기화
for(i = 0; i < n; i++)
tempsum += list[i];                     //tempsum에 0~n(MAX_SIZE)까지 누적해 더하기
return tempsum;
}