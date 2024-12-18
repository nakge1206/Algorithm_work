#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
#include <algorithm>
#include <map>
using namespace std;

// 그래프, bestSolution 정의, bestCost 무한대로 정의
unordered_map<string, unordered_map<string, int>> graph;
vector<string> best_solution;
int best_cost = INT_MAX;

// 간선추가
void addEdge(const string& from, const string& to, int cost) {
    graph[from][to] = cost;
    graph[to][from] = cost;
}

void BacktrackTSP(vector<string>& tour, int curr_cost) {
    string curr_city = tour.back();

    //tour가 완전한 해일때
    if (tour.size() == graph.size()) {
        int total_cost = curr_cost + graph[curr_city]["A"];
        if (total_cost < best_cost) {
            best_cost = total_cost;
            best_solution = tour;
            best_solution.push_back("A"); // 시작점으로 돌아오는 경로 추가
        }
    }

    //현재 graph는 E,B,D,C,A 순으로 되어있음. 역방향으로 되어있어서 map을 이용해 정렬시켜줌
    map<string, int> neighbors(graph[curr_city].begin(), graph[curr_city].end());
    for (const auto& neighbor : neighbors) {
        //이때 neightbor는 {"도시이름", 가중치} 로 되어있음
        string nextCity = neighbor.first;
        int edgeCost = neighbor.second;

        //중복되지 않고, best_cost보다 작을때만 수행
        if (find(tour.begin(), tour.end(), nextCity) == tour.end() && curr_cost + edgeCost < best_cost) {
            tour.push_back(nextCity);
            BacktrackTSP(tour, curr_cost + edgeCost);
            tour.pop_back();
        }
    }
}

int main() {
    //그래프 정의
    addEdge("A", "B", 2);
    addEdge("A", "C", 7);
    addEdge("A", "D", 3);
    addEdge("A", "E", 10);
    addEdge("B", "C", 3);
    addEdge("B", "D", 5);
    addEdge("B", "E", 4);
    addEdge("C", "D", 6);
    addEdge("C", "E", 1);
    addEdge("D", "E", 9);

    //시작점 설정 및 백트래킹 시작
    vector<string> tour = {"A"};
    BacktrackTSP(tour, 0);

    // 결과 출력
    cout <<"[";
    for (int i = 0; i < best_solution.size(); ++i) {
        cout << best_solution[i];
        if (i != best_solution.size() - 1) {
            cout << ", ";
        }
    }
    cout << "], 거리: " << best_cost << endl;

    return 0;
}