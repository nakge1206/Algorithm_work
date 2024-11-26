#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

string mergeFiles(const string& file1, const string& file2, int merge_number) {
    ifstream inFile1(file1), inFile2(file2);
    string merge_name = "merge_" + to_string(merge_number) + ".txt";
    ofstream outFile(merge_name);


    //각 파일에서 num 1,2를 읽어오는데 1은 읽고 2를 못읽으면 2를 저장, 반대면 1저장, 둘다 읽어왔을때는 대소 구분 후 저장
    int num1, num2;
    bool bool_num1 = (inFile1 >> num1) ? true : false;
    bool bool_num2 = (inFile2 >> num2) ? true : false;

    while (bool_num1 || bool_num2) {
        if (!bool_num1) {
            outFile << num2 << "\n";
            bool_num2 = (bool)(inFile2 >> num2) ? true : false; 
        } else if (!bool_num2) {
            outFile << num1 << "\n";
            bool_num1 = (bool)(inFile1 >> num1) ? true : false;
        } else if (num1 <= num2) {
            outFile << num1 << "\n";
            bool_num1 = (bool)(inFile1 >> num1) ? true : false;
        } else {
            outFile << num2 << "\n";
            bool_num2 = (bool)(inFile2 >> num2) ? true : false;
        }
    }

    inFile1.close();
    inFile2.close();
    outFile.close();

    remove(file1.c_str());
    remove(file2.c_str());

    return merge_name;
}

void externalSort(const string& input_name, const string& output_name, size_t block_size) {
    ifstream inputFile(input_name);
    if (!inputFile.is_open()) {
        cerr << "파일 열기 실패" << endl;
        return;
    }

    vector<string> A_HDD;
    vector<string> B_HDD;
    vector<int> block;
    int block_number = 0;

    int value;
    while (inputFile >> value) {
        block.push_back(value);

        if (block.size() == block_size) {
            insertionSort(block);

            string temp_block = "temp_" + to_string(block_number++) + ".txt";
            ofstream tempFile(temp_block);
            for (size_t i = 0; i < block.size(); i++) {
                tempFile << block[i] << "\n";
            }
            tempFile.close();

            A_HDD.push_back(temp_block);

            block.clear();
        }
    }
    // 블럭을 다 못채운 숫자들 처리
    if (!block.empty()) {
        insertionSort(block);

        string temp_block = "temp_" + to_string(block_number++) + ".txt";
        ofstream tempFile(temp_block);
        for (int num : block) {
            tempFile << num << "\n";
        }
        tempFile.close();

        A_HDD.push_back(temp_block);
    }
    inputFile.close();

    int merge_number = 0;
    while (A_HDD.size() > 1) {
        B_HDD.clear();
        for (size_t i = 0; i < A_HDD.size(); i += 2) {
            if (i + 1 < A_HDD.size()) { //짝수개일땐 병합
                string mergedFile = mergeFiles(A_HDD[i], A_HDD[i + 1], merge_number++);
                B_HDD.push_back(mergedFile);
            } else { //홀수일때는 그냥 저장
                B_HDD.push_back(A_HDD[i]);
            }
        }
        A_HDD = B_HDD;
    }

    if (!A_HDD.empty()) {
        rename(A_HDD[0].c_str(), output_name.c_str());
    }

    cout << "정렬 및 출력(external_output.txt) 완료 " << endl;
}

int main() {
    const string input_name = "input.txt";
    const string output_name = "external_output.txt";
    const size_t blockSize = 100;

    externalSort(input_name, output_name, blockSize);

    return 0;
}