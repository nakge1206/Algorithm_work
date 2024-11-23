#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int getMax(const vector<int>& A) {
    return *max_element(A.begin(), A.end());
}

void radixSort_lsd(vector<int>& A) {
    int max = getMax(A);
    int n = A.size();

    for (int exp = 1; max / exp > 0; exp *= 10) {
        vector<int> temp_out(n);
        vector<int> count(10, 0);

        for (int i = 0; i < n; i++) {
            int number = (A[i] / exp) % 10;
            count[number]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int number = (A[i] / exp) % 10;
            temp_out[count[number] - 1] = A[i];
            count[number]--;
        }

        for (int i = 0; i < n; i++) {
            A[i] = temp_out[i];
        }
    }
}

int main() {
    const string input_name = "input.txt";
    const string output_name = "radix_lsd_output.txt";

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

    radixSort_lsd(A);

    ofstream outputFile(output_name);
    if (!outputFile.is_open()) {
        cerr << "파일 쓰기 실패" << endl;
        return 1;
    }

    for(int i = 0; i<A.size(); i++){
        outputFile << A[i] << endl;
    }
    outputFile.close();

    cout << "정렬 및 출력(radix_lsd_output.txt) 완료" << endl;

    return 0;
}