
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>

using namespace std;

class UnionFind {
public:
    vector<size_t> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    //u가 포함된 첫 노드 찾기
    size_t find(size_t u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    //u, v가 포함된 집합 찾기
    bool unionSets(size_t u, size_t v) { 
        size_t rootU = find(u);
        size_t rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
            return true;
        }
        return false;
    }
};

struct Edge {
    int u, v, weight;
};
bool weight(const Edge& e1, const Edge& e2) {
    if(e1.weight == e2.weight){
        return e1.u < e2.u;
    }
    return e1.weight < e2.weight;
}

vector<Edge> kruskal(vector<Edge>& edges) {
    vector<Edge> Tree; //리턴될거

    set<int> vertices;
    for (const auto& edge : edges) {
        vertices.insert(edge.u);
        vertices.insert(edge.v);
    }

    int n = vertices.size(); 
    sort(edges.begin(), edges.end(), weight);
    UnionFind uf(n);
    int mst_weight = 0;

    for (auto& edge : edges) {
        if (edge.u > edge.v) {
            swap(edge.u, edge.v);
        }

        if (uf.unionSets(edge.u, edge.v)) {
            mst_weight += edge.weight;
            Tree.push_back(edge);
        }
    }

    return Tree;
}
int main() {
    vector<Edge> edges = {
        {0, 1, 8}, {0, 3, 2}, {0, 4, 4}, {1, 2, 1}, {1, 3, 4}, {1, 5, 2}, {2, 5, 1}, {3, 4, 3}, {3, 5, 7}, {4, 5, 9}
    };

    clock_t start, end;
    start = clock();
    vector<Edge> tree = kruskal(edges);
    end = clock();

    for (const auto& edge : tree) {
        cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ")\n";
    }

    cout << "\nKruskal_RunningTime: " << (double)(end-start) << " ms" << "\n" << endl;

    return 0;
}

