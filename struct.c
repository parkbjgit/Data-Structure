#include <stdio.h>
struct student1 {              //student1 구조체 정의
char lastName;                 
int studentId;
char grade;
};
typedef struct {              //구조체를 정의하면서 alias
char lastName;
int studentId;
char grade;
} student2;
int main() {
printf("---------ParkBeomJun---------\n");
struct student1 st1 = {'A', 100, 'A'};          //변수 student1 st1에 값 입력
printf("st1.lastName = %c\n", st1.lastName);    //st1의 lastName 출력
printf("st1.studentId = %d\n", st1.studentId);  //st1의 studentId 출력
printf("st1.grade = %c\n", st1.grade);          //st1의 grade 출력
student2 st2 = {'B', 200, 'B'};                 //구조체변수 st2 선언과 값 입력
printf("\nst2.lastName = %c\n", st2.lastName);  //st2의 lastName 출력
printf("st2.studentId = %d\n", st2.studentId);  //st2의 studentId 출력
printf("st2.grade = %c\n", st2.grade);          //st2의 grade 출력
student2 st3;                                   //sudent2형 st3 선언
st3 = st2;                                      //st2값을 st3에 입력
printf("\nst3.lastName = %c\n", st3.lastName);  //st3의 lastName 출력
printf("st3.studentId = %d\n", st3.studentId);  //st3의 studentId 출력
printf("st3.grade = %c\n", st3.grade);          //st3의 grade 출력
/* equality test */
if(st3 == st2) /* not working */               //구조체 자체를 비교할 수는 없음
printf("equal\n");                             //구조체의 원소를 각각 하나씩 비교해줘야함
else                                           //오류이므로 실행되지 않음
printf("not equal\n");
return 0;
}