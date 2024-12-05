#include <stdio.h>
#include <stdlib.h>

#define max 50
#define C 10
#define size 8

int items[size] = {7, 5, 6, 4, 2, 3, 7, 5};

typedef struct {
    int B[max][C]; //최대 30개, 개당용량 C
    int B_count; //사용한 통
} BinPackingResult;

// bin 초기화
void clear(BinPackingResult *result) {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < C; j++) {
            result->B[i][j] = 0;
        }
    }
    result->B_count = 0;
}

// 결과 출력
void printResult(const char *method, BinPackingResult *result) {
    printf("%s:\n", method);
    for (int i = 0; i < result->B_count; i++) {
        printf("Bin%d = [", i + 1);
        int first = 1;
        for (int j = 0; j < C; j++) {
            if (result->B[i][j] > 0) {
                if (!first) printf(", ");
                printf("%d", result->B[i][j]);
                first = 0;
            }
        }
        printf("]\n");
    }
    printf("\n");
}

void firstFit(BinPackingResult *result) {
    for (int i = 0; i < size; i++) {
        int placed = 0;
        for (int j = 0; j < result->B_count; j++) {
            int bin_sum = 0;
            for (int k = 0; k < C; k++) {
                bin_sum += result->B[j][k];
            }
            if (bin_sum + items[i] <= C) {
                for (int k = 0; k < C; k++) {
                    if (result->B[j][k] == 0) {
                        result->B[j][k] = items[i];
                        placed = 1;
                        break;
                    }
                }
                if (placed) break;
            }
        }
        if (!placed) {
            result->B[result->B_count][0] = items[i];
            result->B_count++;
        }
    }
}

void nextFit(BinPackingResult *result) {
    int current_bin = 0;
    int current_sum = 0;

    for (int i = 0; i < size; i++) {
        if (current_sum + items[i] <= C) {
            for (int j = 0; j < size; j++) {
                if (result->B[current_bin][j] == 0) {
                    result->B[current_bin][j] = items[i];
                    break;
                }
            }
            current_sum += items[i];
        } else {
            current_bin++;
            result->B[current_bin][0] = items[i];
            current_sum = items[i];
        }
        if (current_bin + 1 > result->B_count) {
            result->B_count = current_bin + 1;
        }
    }
}

void bestFit(BinPackingResult *result) {
    for (int i = 0; i < size; i++) {
        int best_bin = -1;
        int min_space_left = C + 1;
        for (int j = 0; j < result->B_count; j++) {
            int bin_sum = 0;
            for (int k = 0; k < C; k++) {
                bin_sum += result->B[j][k];
            }
            int space_left = C - bin_sum;
            if (space_left >= items[i] && space_left < min_space_left) {
                best_bin = j;
                min_space_left = space_left;
            }
        }

        if (best_bin == -1) {
            result->B[result->B_count][0] = items[i];
            result->B_count++;
        } else {
            for (int k = 0; k < C; k++) {
                if (result->B[best_bin][k] == 0) {
                    result->B[best_bin][k] = items[i];
                    break;
                }
            }
        }
    }
}

void worstFit(BinPackingResult *result) {
    for (int i = 0; i < size; i++) {
        int worst_bin = -1;
        int max_space_left = -1;

        for (int j = 0; j < result->B_count; j++) {
            int bin_sum = 0;
            for (int k = 0; k < C; k++) {
                bin_sum += result->B[j][k];
            }
            int space_left = C - bin_sum;
            if (space_left >= items[i] && space_left > max_space_left) {
                worst_bin = j;
                max_space_left = space_left;
            }
        }

        if (worst_bin == -1) {
            result->B[result->B_count][0] = items[i];
            result->B_count++;
        } else {
            for (int k = 0; k < C; k++) {
                if (result->B[worst_bin][k] == 0) {
                    result->B[worst_bin][k] = items[i];
                    break;
                }
            }
        }
    }
}

int main() {
    BinPackingResult result;

    clear(&result);
    firstFit(&result);
    printResult("Output1 (First Fit)", &result);

    clear(&result);
    nextFit(&result);
    printResult("Output2 (Next Fit)", &result);

    clear(&result);
    bestFit(&result);
    printResult("Output3 (Best Fit)", &result);

    clear(&result);
    worstFit(&result);
    printResult("Output4 (Worst Fit)", &result);

    return 0;
}