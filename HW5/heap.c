#include <stdio.h>
#include <stdlib.h>

void DownHeap(int A[], int n, int i){
    int bigger = i;
    int leftChild = 2 * i;
    int rightChild = 2 * i + 1;

    if (leftChild <= n && A[leftChild] > A[bigger]) {
        bigger = leftChild;
    }

    if (rightChild <= n && A[rightChild] > A[bigger]) {
        bigger = rightChild;
    }

    if (bigger != i) {
        int temp = A[i];
        A[i] = A[bigger];
        A[bigger] = temp;

        DownHeap(A, n, bigger);
    }
}

void BuildHeap(int A[], int n){
    for(int i = n / 2; i >= 1; i--){
        DownHeap(A, n, i);
    }
}

void heapSort(int A[], int n) {
    BuildHeap(A, n);

    int heapSize = n;
    for (int i = 1; i < n; i++) {
        int temp = A[1];
        A[1] = A[heapSize];
        A[heapSize] = temp;

        heapSize--;
        
        DownHeap(A, heapSize, 1);
    }
}

int main() {
    const char *input_name = "input.txt";
    const char *output_name = "heap_output.txt";

    FILE *inputFile = fopen(input_name, "r");
    if (inputFile == NULL) {
        perror("파일 읽기 실패");
        return EXIT_FAILURE;
    }

    int arr[10000];
    int count = 0;

    while (fscanf(inputFile, "%d", &arr[count+1]) == 1) {
        count++;
    }
    fclose(inputFile);

    heapSort(arr, count);

    FILE *outputFile = fopen(output_name, "w");
    if (outputFile == NULL) {
        perror("파일 쓰기 실패");
        return EXIT_FAILURE;
    }

    for (int i = 1; i <= count; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }
    fclose(outputFile);

    printf("정렬 및 출력(heap_output.txt) 완료 \n");

    return 0;
}