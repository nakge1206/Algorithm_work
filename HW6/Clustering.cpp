#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <limits>

using namespace std;

struct Point {
    int x, y;
};

//거리 계산
double Distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool check_center(const vector<Point>& centers, const Point& point) {
    for (const auto& center : centers) {
        if (center.x == point.x && center.y == point.y) {
            return true;
        }
    }
    return false;
}

//txt파일에서 좌표읽기
vector<Point> readPoint(const string& name) {
    vector<Point> points;
    ifstream file(name);
    if (!file.is_open()) {
        cerr << "파일 열기 실패 " << name << endl;
        exit(1);
    }

    set<pair<int, int>> no_dup;

    int x, y;
    while (file >> x >> y) {
        if (no_dup.find({x, y}) == no_dup.end()) {
            no_dup.insert({x, y});
            points.push_back({x, y});
        }
    }

    file.close();
    return points;
}

//cluster 알고리즘
vector<vector<Point>> Approx_k_Clusters(vector<Point>& points, int k) {
    vector<Point> centers;
    vector<vector<Point>> clusters(k);
    vector<double> min_distances(points.size(), numeric_limits<double>::max());

    centers.push_back(points[0]);

    for (int j = 1; j < k; ++j) {
        int maxIndex = -1;
        double max_min_distance = -1.0;

        for (size_t i = 0; i < points.size(); ++i) {
            if (check_center(centers, points[i])) {
                continue;
            }
            double distance = Distance(points[i], centers[j - 1]);
            min_distances[i] = min(min_distances[i], distance);
            if (min_distances[i] > max_min_distance) {
                max_min_distance = min_distances[i];
                maxIndex = i;
            }
        }
        centers.push_back(points[maxIndex]);
    }

    for (const auto& point : points) {
        double min = numeric_limits<double>::max();
        int cluster = -1;

        for (int j = 0; j < k; ++j) {
            double distance = Distance(point, centers[j]);
            if (distance < min) {
                min = distance;
                cluster = j;
            }
        }
        clusters[cluster].push_back(point);
    }

    return clusters;
}

void print_clusters(const vector<vector<Point>>& clusters, const vector<Point>& centers) {
    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << "Cluster " << i + 1 << " (Center: " << centers[i].x << ", " << centers[i].y << "):" << endl;
        for (const auto& point : clusters[i]) {
            cout << "(" << point.x << ", " << point.y << ") ";
        }
        cout << endl << endl;
    }
}

int main() {
    string filename = "clustering_input.txt";
    int k = 8;

    vector<Point> points = readPoint(filename);

    vector<vector<Point>> clusters = Approx_k_Clusters(points, k);

    vector<Point> centers;
    for (const auto& cluster : clusters) {
        if (!cluster.empty()) {
            centers.push_back(cluster[0]);
        }
    }

    print_clusters(clusters, centers);

    return 0;
}