#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

int matrixChainOrder(vector<int> dimensions, vector<vector<int>>& C) {
    int n = dimensions.size();
    for (int i = 1; i < n; i++) {
        C[i][i] = 0;
    }

    for (int L = 1; L < n-1; L++) {
        for (int i = 1; i < n - L; i++) {
            int j = i + L;
            C[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int temp = C[i][k] + C[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (temp < C[i][j]) {
                    C[i][j] = temp;
                }
            }
        }
    }
    return C[1][n-1];
}

void printMatrix(const vector<vector<int>>& C) {
    int n = C.size();
    cout << "C\t";
    for (int j = 1; j < n; ++j) {
        cout << j << "\t";
    }
    cout << endl;

    for (int i = 1; i < n; ++i) {
        cout << i << "\t";
        for (int j = 1; j < n; ++j) {
            if (i > j) {
                cout << "\t";
            } else if (C[i][j] == INT_MAX) {
                cout << "INF\t";
            } else {
                cout << C[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

vector<int> find_demensions(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일열기 실패" << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    vector<int> d;
    int temp;

    while (getline(file, line)) {
        if (line.find("A") != string::npos && line.find("=") != string::npos) {
            int rows = 1, cols = 0;
            while (getline(file, line) && line.find("[") != string::npos) {
                rows++;
                if (cols == 0) {
                    line.erase(remove_if(line.begin(), line.end(), [](char c) { return c == '[' || c == ']'; }), line.end());
                    stringstream ss(line);
                    int val;
                    cols = 0;
                    while (ss >> val) {
                        cols++;
                    }
                }
            }
            if (d.empty()) {
                d.push_back(rows);
                d.push_back(cols);
                temp = cols;
            }else if(rows == temp){
                d.push_back(cols);
                temp = cols;
            }
        }
    }
    cout << endl;
    return d;
}

int main() {
    string filename = "matrix_input.txt";
    vector<int> dimensions = find_demensions(filename);

    if (dimensions.size() < 2) {
        cerr << "행렬이 2개이상 있어야 계산 가능합니다." << endl;
        return EXIT_FAILURE;
    }

    int n = dimensions.size();

    vector<vector<int>> C(n, vector<int>(n, INT_MAX));

    int minCost = matrixChainOrder(dimensions, C);

    cout << "최소 곱셈 횟수: " << minCost << endl;
    cout << "행렬 곱셈 최소 비용 테이블:" << endl;
    printMatrix(C);

    return 0;
}