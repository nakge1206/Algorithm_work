#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void insertionSort(vector<int> &A) {
    for (size_t i = 1; i < A.size(); i++) {
        int CurrentElement = A[i];
        int j = i - 1;

        while (j >= 0 && (A[j] > CurrentElement)) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = CurrentElement;
    }
}

int main() {
    const string input_name = "input.txt";
    const string output_name = "insertion_output.txt";

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

    insertionSort(A);

    ofstream outputFile(output_name);
    if (!outputFile.is_open()) {
        cerr << "파일 쓰기 실패" << endl;
        return 1;
    }

    for(int i = 0; i<A.size(); i++){
        outputFile << A[i] << endl;
    }
    outputFile.close();

    cout << "정렬 및 출력(insertion_output.txt) 완료" << endl;
    return 0;
}