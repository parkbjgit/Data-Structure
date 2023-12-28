#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int** a);
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function으로 구현 */
int quickSort(int* a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int* a, int** ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key);

int main()
{
	char command;
	int* array = NULL;
	int* hashtable = NULL;
	int key = -1;
	int index = -1;
    printf("------------------2021041022   Park Beom Jun--------------------\n");
	srand(time(NULL));

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z': // 초기화
			initialize(&array);
			break;
		case 'q': case 'Q': // 배열 메모리 해제
			freeArray(array);
			break;
		case 's': case 'S': // 선택정렬
			selectionSort(array);
			break;
		case 'i': case 'I': // 삽입정렬
			insertionSort(array);
			break;
		case 'b': case 'B': // 버블정렬
			bubbleSort(array);
			break;
		case 'l': case 'L': // 셸정렬
			shellSort(array);
			break;
		case 'k': case 'K': // 퀵정렬
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H': // 해싱
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E': // 데이터 찾기
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': // 배열출력
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) // 배열 초기화
{
	int* temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) { // 배열이 비어있으면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 채우기
		temp[i] = rand() % MAX_ARRAY_SIZE;
	return 0;
}

int freeArray(int* a) // 메모리 해제
{
	if (a != NULL)
		free(a);
	return 0;
}

void printArray(int* a) // 전체 배열 출력
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

int selectionSort(int* a) // 선택정렬
{
	int min; // 최솟값을 담을 변수
	int minindex; // 최솟값의 인덱스를 담아줄 변수
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 기존 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 배열의 크기만큼 반복문을 돌면서
	{
		minindex = i; // 리스트의 i번째 원소의 인덱스 지정
		min = a[i]; // 일단 리스트의 i번째 원소를 min이라 해둠 
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
			// 앞에서 지정한 i번째 원소 다음부터, 배열전체를 돌면서 최솟값 찾아내기
		{
			if (min > a[j]) // i번째 원소보다 작은 값을 찾았으면, 
			{
				min = a[j]; // 그 값을 min으로 하고
				minindex = j; // 그때의 인덱스j를 minindex로 하기
			}
		}
		a[minindex] = a[i]; // i번째 원소(리스트의 첫번째)로 지정해둔 데이터를, 찾아낸 최솟값 자리로 이동
		a[i] = min; // 찾아낸 최솟값을 리스트의 첫번째 자리로 이동
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int* a) // 삽입정렬
{
	int i, j, t;
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);

	for (i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // t값이 배열의 1번째 원소부터 시작 
		j = i;
		while (a[j - 1] > t&& j > 0) // 들어갈 위치를 찾고하자하는 t보다 앞에위치한 원소가 클경우(인덱스는 양수)
		{
			a[j] = a[j - 1]; // 앞 원소 값을 바로 뒷칸에 넣어줌 -> 한칸씩 뒤로 밀기
			j--; // j값 감소 -> 큰 숫자들을 뒤로 보내면서, t가 들어갈 자리 찾기
		}
		a[j] = t; // t를 위의 반복문에서 정렬완료된 자리에 넣어주기
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int bubbleSort(int* a) // 버블정렬
{
	int i, j, t;
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 배열의 크기만큼 반복하기
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // 배열 한바퀴 돌기
		{
			if (a[j - 1] > a[j]) // 배열의 인접요소끼리 비교 - 앞이 뒤보다 크면
			{
				t = a[j - 1]; // 앞 원소를 잠시 빼두고
				a[j - 1] = a[j]; // 그자리에 뒤에 위차한 원소를 넣고
				a[j] = t; // 빼둔 앞 원소를 뒤에 넣어주기 -> 앞뒤 위치교환
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int shellSort(int* a) // 셸 정렬
{
	int i, j, k, h, v;
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) // 초기 h값을 배열크기의 절반으로 지정
												// 정렬이 수행될수록 h의 크기는 절반씩 감소
	{
		for (i = 0; i < h; i++)// 첫 원소부터 간격이 h만큼 떨어진 위치에 있는 원소와 비교하여 위치 정렬
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)  // 간격이 h인 레코드들끼리 삽입정렬
			{
				v = a[j]; // 비교할 두개의 원소중, 뒤에 있는 원소를 v라 하고
				k = j; // 그때의 인덱스를 k라 한다
				while (k > h - 1 && a[k - h] > v) // h간격 만큼 떨어진 원소 비교 
		        //- 앞원소가 h간격 만큼 떨어진 위치에 있는 원소보다 크면 두개의 자리를 바꿔야함.
				{
					a[k] = a[k - h]; // 앞에 위치한 원소를 뒷자리로 옮기기
					k -= h; // 인덱스 k를 h만큼 앞으로 
				}
				a[k] = v; // 뒷자리 원소를 앞자리에 넣기
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int quickSort(int* a, int n) // 퀵정렬
{
	int v, t;
	int i, j;
	if (n > 1) // 배열의 크기가 1보다 크면,
	{
		v = a[n - 1]; // = pivot / 배열의 마지막 원소를 v로 하기
		i = -1; 
		j = n - 1; // 마지막 원소의 인덱스를 j로 하기 

		while (1)
		{
			while (a[++i] < v); 
			// 배열의 처음부터 인덱스 값을 증가시키면서, 마지막 원소보다 큰 값을 만나면 반복문 탈출
			while (a[--j] > v);
			// 배열의 마지막 원소부터 마지막 원소보다 작은 값을 만나면 반복문 탈출

			if (i >= j) break; // i가 j보다 커지면(배열의 뒷쪽에 있으면) 무한 반복문 탈출
			t = a[i]; // i가 j보다 작으면, a[i]와 a[j]의 값을 교환시켜주기
			a[i] = a[j];
			a[j] = t;
		}
		// i가 j보다 커지면(배열의 뒷쪽에 있으면) a[i]와 pivot값(마지막 원소)을 교환하기
		t = a[i]; 
		a[i] = a[n - 1]; // 위치 a[i]가 pivot이 되는 것
		a[n - 1] = t;

		quickSort(a, i); // 인덱스 i를 중심으로 왼쪽 집합과 오른쪽 집합을 구분하여 퀵정렬을 다시 호출
		quickSort(a + i + 1, n - i - 1);
	}
	return 0;
}

int hashCode(int key) { // 제산함수 사용
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int* a, int** ht) // 해싱_ 배열에 대한 해시테이블 만들기
{
	int* hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 배열의 size만큼
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // 할당받은 해시테이블의 값을 전부 -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 전체를 돌면서
	{
		key = a[i];
		hashcode = hashCode(key); // hashcode는 홈 버킷주소
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) // 해시테이블이 비어있으면,
		{
			hashtable[hashcode] = key; // 해시 테이블에 key값 할당
		}
		else { // 해시테이블이 비어있지않으면
			index = hashcode; // hashcode 값을 index에 할당

			while (hashtable[index] != -1) // 해시테이블의 빈공간 찾기
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // hashcode 재조정
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; // 찾은 빈공간 해시 테이블에 key값 할당
		}
	}
	return 0;
}

int search(int* ht, int key) // 해시테이블에서 key찾기
{
	int index = hashCode(key); // 전달받은 key값의 hashtable 주소 찾기

	if (ht[index] == key) // table에서 key값을 찾았으면, index값 반환
		return index;

	while (ht[++index] != key) // key를 찾을때까지
	{
		index = index % MAX_HASH_TABLE_SIZE; //index 조정
	}
	return index; // 해당 hashcode 값 리턴
}