#include <stdio.h>
#include <stdlib.h>

void selectionSort(int A[], int n) {
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        int temp = A[min];
        A[min] = A[i];
        A[i] = temp;
    }
}

int main() {
    char *input_name = "input.txt";
    char *output_name = "selection_output.txt";

    FILE *inputFile = fopen(input_name, "r");
    if (inputFile == NULL) {
        perror("파일 열기 실패");
        return EXIT_FAILURE;
    }

    int A[10000];
    int count = 0;

    while (fscanf(inputFile, "%d", &A[count]) == 1) {
        count++;
    }
    fclose(inputFile);

    selectionSort(A, count);

    FILE *outputFile = fopen(output_name, "w");
    if (outputFile == NULL) {
        perror("파일 쓰기 실패");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "%d\n", A[i]);
    }
    fclose(outputFile);

    printf("정렬 및 출력(selection_output.txt) 완료\n");

    return 0;
}