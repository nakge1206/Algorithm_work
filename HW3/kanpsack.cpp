#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Goods
{
    string name;
    int gram;
    int value;
    int valuepgram;

    bool operator<(const Goods& other) const{
        return valuepgram > other.valuepgram;
    }
};

struct knapsack_result
{
    vector<Goods> names;
    int total_gram;
    int total_value;
};


knapsack_result Knapsack(vector<Goods>& goods, int max_weight){
    for(auto& good : goods){
        good.valuepgram = good.value / good.gram;
    }
    sort(goods.begin(), goods.end());

    knapsack_result result;
    result.total_gram = 0;
    result.total_value = 0;

    for (auto& good : goods) {
        if (result.total_gram + good.gram <= max_weight) {
            // 물건 전체를 배낭에 넣을 수 있는 경우
            result.total_gram += good.gram;
            result.total_value += good.value;
            result.names.push_back(good);
        } else {
            // 물건의 일부만 배낭에 넣을 수 있는 경우
            int re_gram = max_weight - result.total_gram;
            Goods sub_good = good;
            sub_good.gram = re_gram;
            sub_good.value = good.valuepgram * re_gram;

            result.total_gram += re_gram;
            result.total_value += sub_good.value;
            result.names.push_back(sub_good);
            break;
        }
    }
    return result;
}

int main() {
    vector<Goods> goods = {
        {"백금", 10, 60000, 0},
        {"금", 15, 50000, 0},
        {"은", 25, 4000, 0},
        {"주석", 50, 1000, 0}
    };

    clock_t start, end;
    start = clock();
    knapsack_result result = Knapsack(goods, 40);
    end = clock();

   cout << "Goods" << "     Weight of goods in knapsack" << "     Value of goods in knapsack\n";
    for (const auto& good : result.names) {
        cout << good.name << "\t\t\t" << good.gram << "\t\t\t\t" << good.value << endl;
    }
    cout <<"Sum\t\t\t" << result.total_gram << "\t\t\t\t" << result.total_value << endl;
    cout << "\nKruskal_RunningTime: " << (double)(end-start) << " ms" << "\n" << endl;

    return 0;
}

