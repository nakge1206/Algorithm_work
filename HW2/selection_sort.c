#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int* A, int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int Selection(int*A, int left, int right, int k){
    //left~right에서 랜덤한 pivot 고르기
    int pivot = rand() % (right - left + 1) + left;
    //pivot과 A[left] 자리 바꾸기
    swap(A, pivot, left);

    int small = left, big = right;
    int pivot_value = A[left];

    while (small < big) {
        while (big > left && A[big] >= pivot_value) {
            big--;
        }
        while (small <= right && A[small] <= pivot_value) {
            small++;
        }
        if (small < big) {
            swap(A, small, big);
        }
    }
    swap(A, left, big);

    int S = (big-1)-left+1;
    if(k<=S) Selection(A,left,big-1,k);
    else if(k==S+1) return A[big];
    else Selection(A, big+1, right, k-S-1);
}

int main() {
    //input 파일 읽고 Array 저장 (50번째, 70번째에 대한 배열을 다르게 준비)
    FILE *fin = fopen("input_sort.txt", "r");
    if(fin == NULL){
        printf("open error\n");
        return 1;
    }
    int count = 0, temp;
    while(fscanf(fin, "%d", &temp) != EOF) count++;
    rewind(fin);
    int* Array_1 = (int*)malloc(count* sizeof(int));
    for(int i=0; i<count; i++) fscanf(fin, "%d", &Array_1[i]);
    fclose(fin);
    int* Array_2 = (int*)malloc(count * sizeof(int));  // Array와 동일한 크기의 배열 할당
    memcpy(Array_2, Array_1, count * sizeof(int));  // Array의 내용을 ArrayCopy로 복사


    //running time 측정, Seection 시작, 결과값 및 RunningTime 출력
    clock_t start, end;
    int k = 50;
    if(k < 1 || k >count-1){
        printf("k error");
        return 1;
    }
    start = clock();
    int a = Selection(Array_1, 0, count-1, k);
    end = clock();
    printf("50's : %d \n", a);
    printf("Selection_RunningTime_%d : %f ms \n", k, (double)(end - start) / CLOCKS_PER_SEC * 1000);

    k = 70;
    if(k < 1 || k >count-1){
        printf("k error");
        return 1;
    }
    start = clock();
    int b = Selection(Array_2, 0, count-1, k);
    end = clock();
    printf("70's : %d \n", b);
    printf("Selection_RunningTime_%d : %f ms \n", k, (double)(end - start) / CLOCKS_PER_SEC * 1000);

    free(Array_1);
    free(Array_2);

    return 0;
}

