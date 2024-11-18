// 인접 행렬 초기화
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0; // 자기 자신으로 가는 경로의 가중치는 0
            } else {
                graph[i][j] = INF; // 초기에는 모든 경로를 무한대로 설정
            }
        }
    }