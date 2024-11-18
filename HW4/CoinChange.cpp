#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;


vector<int> coinChange(int n, vector<int> coins) {
    vector<int> C(n + 1, INT_MAX);
    C[0] = 0;

    for (int j = 1; j <= n; ++j) {
        for (int i = 0; i<coins.size(); i++){
            if(coins[i] <= j && C[j-coins[i]]+1 < C[j]){
                C[j] = C[j-coins[i]] + 1;
            }
        }
    }

    return C;
}

int main() {
    int n = 20;
    vector<int> coins = {16, 10, 5, 1};

    vector<int> result = coinChange(n, coins);

    cout << setw(3) << left << "j:";
    for (int i = 0; i <= n; ++i) {
        cout << setw(3) << left << i << " ";
    }
    cout << endl;
    cout << setw(3) << left << "c:";
    for (int i = 0; i <= n; ++i) {
        cout << setw(3) << left << result[i] << " ";
    }
    cout << endl;

    return 0;
}