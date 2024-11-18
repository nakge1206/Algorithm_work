#include <stdio.h>
#include <limits.h>
#include <time.h>

#define V 10       // 도시 개수
#define INF INT_MAX // 무한대 값

const char *cities[V] = {
    "서울", "천안", "논산", "대전", "광주", "부산", "대구", "포항", "원주", "강릉"
};

void FloydWarshall(int graph[V][V], int D[V][V]) {
    // 초기화: dist 배열을 graph 배열로 초기화
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            D[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (D[i][k] != INF && D[k][j] != INF && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

void printD(int D[V][V]){
    printf("       ");
    for(int i=0;i<V;i++) printf("%-10s", cities[i]);
    printf("\n");
    for(int i=0;i<V;i++){
        printf("%-7s", cities[i]);
        printf("   ");
        for(int j=0; j<V; j++){
            if(i<j){
                printf("%-8d", D[i][j]);
            }else{printf("        ");}
            
        }
        printf("\n");
    }

}


int main() {
    int graph[V][V];
    int D[V][V];

    // 간선정보 초기화 및 입력
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }
    graph[0][1] = 12; graph[1][0] = 12; // 서울 - 천안
    graph[0][8] = 15; graph[8][0] = 15; // 서울 - 원주
    graph[1][3] = 10; graph[3][1] = 10; // 천안 - 대전
    graph[1][2] = 4;  graph[2][1] = 4;  // 천안 - 논산
    graph[2][3] = 3;  graph[3][2] = 3;  // 논산 - 대전
    graph[2][4] = 13; graph[4][2] = 13; // 논산 - 광주
    graph[8][9] = 21; graph[9][8] = 21; // 원주 - 강릉
    graph[8][6] = 7;  graph[6][8] = 7;  // 원주 - 대구
    graph[6][5] = 9;  graph[5][6] = 9;  // 대구 - 부산
    graph[9][7] = 25; graph[7][9] = 25; // 강릉 - 포항
    graph[6][7] = 19; graph[7][6] = 19; // 대구 - 포항
    graph[7][5] = 5;  graph[5][7] = 5;  // 포항 - 부산
    graph[3][6] = 10; graph[6][3] = 10; // 대전 - 대구
    graph[4][5] = 15; graph[5][4] = 15; // 광주 - 부산


    clock_t start, end;
    start = clock();
    FloydWarshall(graph, D);
    end = clock();

    printD(D);

    printf("\nFloyd-Warshall Running Time: %.2f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000);

    return 0;
}