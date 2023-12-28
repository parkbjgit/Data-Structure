#include <stdio.h>
#include <stdlib.h>
#include <time.h>                                         //랜덤을 사용하기 위한 전처리기

/* Method Declaration */
int** create_matrix(int row, int col);                    //이중포인터로 2차원 배열 생성
void print_matrix(int** matrix, int row, int col);        //2차원 배열 출력
int free_matrix(int** matrix, int row, int col);          //동적 할당 해제
int fill_data(int** matrix, int row, int col);            //임의의 값을 배열에 할당
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);           //배열을 더해주는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);        //두 배열을 빼는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);            //전치행렬 T 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);           //행렬 A와 전치행렬T를 곱해주는 함수

int main()
{
    char command;                                                          //명령을 입력할 변수
    printf("[----- Park Beom Jun   2021041022 -----]\n");

	int row, col;
	srand(time(NULL));                                                     //임의의 값을 사용

	printf("Input row and col : ");                               
	scanf("%d %d", &row, &col);                                            //행과 열의 값을 입력받기
    int** matrix_a = create_matrix(row, col);                              //행렬 a 를 생성(아직 값은 할당받지 않음)
	int** matrix_b = create_matrix(row, col);                              //행렬 b 를 생성(아직 값은 할당받지 않음)
    int** matrix_a_t = create_matrix(col, row);                            //a의 전치행렬 a_t 생성-row와 col을 서로 교환(아직 값은 할당받지 않음)

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}                 //행렬이 NULL값이라면 비정상 -1을 반환

	do{                                                                                     //q가 입력될때까지 계속 실행
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");             //행렬 각각의 값 생성          출력
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");             //더하기                      빼기
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");             //전치행렬 생성                곱하기
		printf(" Quit                = q \n");                                               //종료
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);                                          //명령어를 입력

		switch(command) {                                                //스위치문을 이용한 명령어 선택
		case 'z': case 'Z':                                              //z를 입력한다면
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);                               //행렬 a,b 각각의 값을 랜덤으로 채우기
			fill_data(matrix_b, row, col);
			break;                                                       //스위치문 빠져나오기
        case 'p': case 'P':                                          //p를 입력한다면
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);                        //행렬 a,b를 각각 출력
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
        case 'a': case 'A':                                          //a를 입력한다면
			printf("Add two matrices\n");                            //행렬 덧셈
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
        case 's': case 'S':                                          //s를 입력한다면
			printf("Subtract two matrices \n");                      //행렬 뺄셈
            subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
        case 't': case 'T':                                          //t를 입력한다면
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);        //행,열을 서로 바꾸는 전치행렬
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M':                                               //m를 입력한다면
			printf("Multiply matrix_a with transposed matrix_a \n");      //행렬 A와 A의 전치행렬T와 곱
			transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
        case 'q': case 'Q':                                              //q를 입력한다면
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);                           //동적할당 해제
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');                           //q가 입력될 때까지 앞 statememt 실행

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)                               //2차원 배열이므로 이중포인터로 생성
{
	/* Check pre conditions */                                    //비정상적인 값을 대비한 검사
	if (row <= 0 || col <= 0) {                                   //모든 함수에 비정상적인 행과 열에 대한 검사
		printf("Check the size of row and col!\n");               //입력한 행과 열을 확인해라 출력
		return NULL;                                              //NULL을 리턴
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);              //정수형으로 행을 메모리 동적할당
	for (int r = 0; r < row; r++) {                                //하나의 행마다 입력받은 열만큼 메모리 동적 할당으로 생성
		matrix[r] = (int*)malloc(sizeof(int) * col);
	}

	/* Check post conditions */
	if (matrix == NULL) {                                          //실행한 후 행렬이 NULL값인지 확인
		printf("Memory Allocation Failed.\n");                     //메모리 할당 실패 출력
		return NULL;
	}

	return matrix;                                                 //행렬을 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)                  //행렬을 출력하는 함수
{
	/* Check pre conditions */                                     
	if (row <= 0 || col <= 0) {                                       
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {       //생성된 행렬을 이중 for문으로 출력
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {                                             
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)                       //동적 메모리 할당을 해제하는 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                                       
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {        //행별로 동적할당을 해제
		free(matrix[matrix_row]);
	}

	free(matrix);                                                     
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)                          //행렬을 이중포인터로 매개
{
	/* Check pre conditions */                                         //비정상적인 값을 대비한 검사
	if (row <= 0 || col <= 0) {                                        //행,열이 0보다 작은 값 입력시 -1 반환
		printf("Check the size of row and col!\n");                    //행렬의 사이즈를 확인하라
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)             //for 문을 이중으로 사용해 각각의 값 생성
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;                //값을 19를 최대로 한정
	/* Check post conditions */
    if (matrix == NULL) {                                                //행렬이 NULL이라면 메모리 할당 실패 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;                                                            //정상
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);                                 
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {                                                 
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {                   //matrix_sum에 행렬 a,b의 합 넣기
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {             //행렬이 NULL값인지 확인
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);                                             //동적할당 해제
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);
	/* Check pre conditions */    
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");                              
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {                        //matrix_sub에 행렬 a-b을 한 값 넣기
		for (int matrix_col = 0; matrix_col < col; matrix_col++)                         
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {               
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);                                           //동적할당 해제

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)                //A의 전치행렬 T 구하기
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)                     //행과 열을 서로 교환시키기
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)                      //행렬 a와 전치행렬 t의 곱
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {                       //행렬 a의 행을 0~마지막행 까지
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {                   //전치행렬 t의 행을 0~마지막행 까지
			int temp = 0;                                                                  //temp 선언+ 0 초기화
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];  //temp에 행렬의 곱셈을 적용해서 곱한 값을 모두 
			matrix_axt[matrix_a_row][matrix_t_row] = temp;                                        //더한 값을 행렬 matrix_axt에 입력
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);                              //동적할당 해제
	return 1;
}
