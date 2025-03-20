#include <stdio.h>
#include <limits.h>
#include <time.h>

#define V 10       // 도시 개수
#define INF INT_MAX // 무한대 값
#define MAX 100 //간선최대 개수

#define Seoul 0
#define Cheonan 1
#define Nonsan 2
#define Daejeon 3
#define Gwangju 4
#define Busan 5
#define Daegu 6
#define Pohang 7
#define Wonju 8
#define Gangneung 9


//여기부터 heap 정의 구간//


// 노드 구조체 정의
typedef struct {
    int location;
    int distance;
} HeapNode;

// 최대 힙 구조체 정의
typedef struct {
    HeapNode data[MAX];
    int size;
} MinHeap;

// 힙 초기화
void initHeap(MinHeap *heap) {
    heap->size = 0;
}

// 힙에 노드 삽입
void insert(MinHeap *heap, int location, int distance) {
    if (heap->size >= MAX) {
        printf("힙이 가득 찼습니다.\n");
        return;
    }

    int i = heap->size++;
    heap->data[i].location = location;
    heap->data[i].distance = distance;

    while (i != 0 && heap->data[(i - 1) / 2].distance > heap->data[i].distance) {
        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// 최소값 삭제
HeapNode deleteMin(MinHeap *heap) {
    if (heap->size <= 0) {
        printf("힙이 비어 있습니다.\n");
        return (HeapNode){-1, INF}; // 실패 시 반환할 기본 값
    }

    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left].distance < heap->data[smallest].distance) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].distance < heap->data[smallest].distance) {
            smallest = right;
        }

        if (smallest != i) {
            HeapNode temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return root;
}

//여기까지 heap 정의 구간//


//간선구조체
typedef struct
{
    int location1;
    int location2;
    int distance;
} Graph;

void add_edge(Graph graph[], int location1, int location2, int distance, int i){
    graph[i].location1 = location1;
    graph[i].location2 = location2;
    graph[i].distance = distance;
    graph[i+1].location1 = location2;
    graph[i+1].location2 = location1;
    graph[i+1].distance = distance;
}

int* dijkstra(Graph graph[], int start_point){
    MinHeap heap;
    initHeap(&heap);
    static int D[V];

    // 초기화
    for (int i = 0; i < V; i++) {
        D[i] = INF;
    }
    D[start_point] = 0;
    insert(&heap, start_point, 0);

    while (heap.size > 0) {
        HeapNode minNode = deleteMin(&heap);
        int u = minNode.location;

        // 간선 배열에서 인접 노드를 찾고 거리 업데이트
        for (int i = 0; i < MAX; i++) {
            if (graph[i].location1 == u) {
                int v = graph[i].location2;

                // 유효한 인덱스인지 확인
                if (v < 0 || v >= V) {
                    break;
                }

                int newDist = D[u] + graph[i].distance;
                if (newDist < D[v]) {
                    D[v] = newDist;
                    insert(&heap, v, newDist);
                }
            }
        }
    }

    return D;
}

const char *cities[V] = {
    "서울", "천안", "논산", "대전", "광주", "부산", "대구", "포항", "원주", "강릉"
};

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
    Graph graph[MAX];
    add_edge(graph, Seoul, Cheonan, 12, 0);
    add_edge(graph, Seoul, Wonju, 15, 2);
    add_edge(graph, Cheonan, Daejeon, 10, 4);
    add_edge(graph, Cheonan, Nonsan, 4, 6);
    add_edge(graph, Nonsan, Daejeon, 3, 8);
    add_edge(graph, Nonsan, Gwangju, 13, 10);
    add_edge(graph, Wonju, Gangneung, 21, 12);
    add_edge(graph, Wonju, Daegu, 7, 14);
    add_edge(graph, Daegu, Busan, 9, 16);
    add_edge(graph, Gangneung, Pohang, 25, 18);
    add_edge(graph, Daegu, Pohang, 19, 20);
    add_edge(graph, Pohang, Busan, 5, 22);

    int distance[V][V];
    
    clock_t start, end;

    start = clock();
    for(int i=0; i<V; i++){
        int *D = dijkstra(graph, i);
        for(int j=0; j<V; j++){
            distance[i][j] = D[j];
        }
    }
    end = clock();

    printD(distance);

    printf("\nDijkstra_RunningTime: %.2f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000);

    return 0;
}

