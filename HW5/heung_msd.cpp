#include <iostream>
#include <fstream>
#include <vector>

void countingSortMSD(const std::vector<int>& arr, int exp, std::vector<int>& output) {
    int count[10] = {0};

    // 개수 세기
    for (int num : arr) {
        count[(num / exp) % 10]++;
    }

    // 누적합 계산
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 출력 배열 구성
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
}

void radixSortMSD(std::vector<int>& arr, int exp) {
    if (arr.size() <= 1) return;

    std::vector<int> output(arr.size());
    countingSortMSD(arr, exp, output);

    // 분할 및 재귀적으로 각 디지트에 대해 정렬
    int start = 0;
    for (int i = 0; i < 10; i++) {
        std::vector<int> bucket;
        for (int num : output) {
            if ((num / exp) % 10 == i) {
                bucket.push_back(num);
            }
        }
        if (!bucket.empty()) {
            radixSortMSD(bucket, exp * 10);
            // 결과를 원래 배열에 삽입
            for (int num : bucket) {
                arr[start++] = num;
            }
        }
    }
    
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("radix_msd_output.txt");

    std::vector<int> numbers;

    if (!inputFile) {
        std::cerr << "입력 파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    int number;
    // 파일에서 정수 읽기
    while (inputFile >> number) {
        numbers.push_back(number);
    }

    inputFile.close();

    // MSD 방법으로 정렬
    radixSortMSD(numbers, 1);
    for (int num : numbers) {
        outputFile << num << std::endl;
    }
    std::cout << "MSD 방법으로 정렬된 결과를 radix_msd_output.txt에 저장했습니다." << std::endl;

    outputFile.close();

    return 0;
}
