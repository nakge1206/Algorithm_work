#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int getMax(const vector<int>& A) {
    return *max_element(A.begin(), A.end());
}

void radix_msd(vector<int>& A, int left, int right, int exp) {
    if (left >= right || exp == 0) return;

    vector<vector<int>> count(10);

    for (int i = left; i <= right; i++) {
        int number = (A[i] / exp) % 10;
        count[number].push_back(A[i]);
    }

    int current_index = left;
    for (int d = 0; d < 10; d++) {
        if (!count[d].empty()) {
            for(int i = 0; i < count[d].size(); i++){
                A[current_index++] = count[d][i];
            }
            radix_msd(A, current_index - count[d].size(), current_index - 1, exp / 10);
        }
    }
}

void radixSort_msd(vector<int>& A) {
    int max = getMax(A);
    int exp = 1;
    while (max / exp >= 10) exp *= 10;

    radix_msd(A, 0, A.size() - 1, exp);
}


int main() {
    const string input_name = "input.txt";
    const string output_name = "radix_msd_output.txt";

    ifstream inputFile(input_name);
    if (!inputFile.is_open()) {
        cerr << "파일 열기 실패" << endl;
        return 1;
    }

    vector<int> A;
    int value;

    while (inputFile >> value) {
        A.push_back(value);
    }
    inputFile.close();

    radixSort_msd(A);

    ofstream outputFile(output_name);
    if (!outputFile.is_open()) {
        cerr << "파일 쓰기 실패" << endl;
        return 1;
    }

    for(int i = 0; i<A.size(); i++){
        outputFile << A[i] << endl;
    }
    outputFile.close();

    cout << "정렬 및 출력(radix_msd_output.txt) 완료" << endl;

    return 0;
}