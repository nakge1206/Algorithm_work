#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <functional>


using namespace std;

//도시 정보 저장
struct City {
    char name;
    int x, y;
};

//MST 계산 결과값
struct Edge {
    char A, B;
    double distance;
};

//출력용
struct output{
    vector<char> cities;
    double totalDistance;
};

//거리계산 함수
double distance(const City& a, const City& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// prim방식으로 mst 계산
vector<Edge> MST(const vector<City>& citys, vector<vector<double>>& distances) {
    int n = citys.size();
    vector<bool> visited(n, false);
    vector<Edge> mst;
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<>> pq;

    //초기화
    visited[0] = true;
    for (int i = 0; i < n; ++i) {
        if(distances[0][i] != 0) {
            pq.push({distances[0][i], {0,i}});
        }   
    }

    //반복
    while(!pq.empty() && mst.size() < n-1){
        auto [weight, endpoints] = pq.top();
        pq.pop();
        int u = endpoints.first, v = endpoints.second;

        if(visited[v]) continue;

        mst.push_back({citys[u].name, citys[v].name, weight});
        visited[v] = true;

        for(int next=0; next<n; ++next){
            if(!visited[next] && distances[v][next] != 0){
                pq.push({distances[v][next], {v, next}});
            }
        }
    }
    return mst;
}

vector<char> MST_path(const vector<Edge>& mst, char starting) {
    unordered_map<char, vector<char>> adjList;
    for (const auto& edge : mst) {
        adjList[edge.A].push_back(edge.B);
        adjList[edge.B].push_back(edge.A); 
    }

    vector<char> path;            
    unordered_set<string> visitedEdges; 
    unordered_set<char> visitedNodes;  

    function<void(char)> dfs = [&](char node) {
        visitedNodes.insert(node);
        path.push_back(node);

        for (char neighbor : adjList[node]) {
            string edgeKey1 = string(1, node) + string(1, neighbor);
            string edgeKey2 = string(1, neighbor) + string(1, node);

            // 아직 방문하지 않은 간선만 탐색
            if (!visitedEdges.count(edgeKey1)) {
                visitedEdges.insert(edgeKey1);
                visitedEdges.insert(edgeKey2); 
                dfs(neighbor);
                path.push_back(node);
            }
        }
    };

    dfs(starting);
    return path;
}

output final_TSP(vector<char> output_before, vector<vector<double>> distances){
    unordered_set<char> visited;
    vector<char> finalPath;
    double totalDistance = 0.0;

    // 중복 제거
    for (char city : output_before) {
        if (!visited.count(city)) {
            visited.insert(city);
            finalPath.push_back(city);
        }
    }

    //시작지점 추가
    finalPath.push_back(finalPath[0]);

    // 총 거리 계산
    for (size_t i = 1; i < finalPath.size(); ++i) {
        char from = finalPath[i - 1];
        char to = finalPath[i];
        int fromIndex = from - 'A';
        int toIndex = to - 'A';
        totalDistance += distances[fromIndex][toIndex];
    }

    return {finalPath, totalDistance};
}

output TSP(vector<City> citys, vector<vector<double>> distances){
    vector<Edge> mst;
    //1단계 MST찾기
    mst = MST(citys, distances);

    //2단계 중복포함 순서 찾기
    vector<char> output_before;
    output_before = MST_path(mst, 'A');

    //3단계 중복부분 제거
    output outputs = final_TSP(output_before, distances);

    return outputs;
}

int main() {
    vector<City> citys = {
        {'A', 0, 3}, {'B', 7, 5}, {'C', 6, 0}, {'D', 4, 3},
        {'E', 1, 0}, {'F', 5, 3}, {'G', 2, 2}, {'H', 4, 1}
    };

    size_t n = citys.size();
    vector<vector<double>> distances(n, vector<double>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            distances[i][j] = distance(citys[i], citys[j]);
        }
    }

    output total;

    total = TSP(citys, distances);

    cout << "이동순서 : ";
    for (char city : total.cities) {
        cout << city << " ";
    }
    cout << "\n이동거리 : " << total.totalDistance << endl;

    return 0;
}