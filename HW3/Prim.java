import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

class Graph {
    int vertexA, vertexB, weight;

    public Graph(int vertexA, int vertexB, int weight) {
        this.vertexA = vertexA;
        this.vertexB = vertexB;
        this.weight = weight;
    }
}

public class Prim {
    public static void main(String[] args) {
        List<Graph> graph = new ArrayList<>();
        List<Graph> tree = new ArrayList<>();
        generateGraph(graph);


        // running time 측정, Prim 시작
        long start = System.nanoTime();
        tree = PrimMST(graph);
        long end = System.nanoTime();

        // MST 출력
        for (Graph edge : tree) {
            System.out.printf("(%d, %d, %d)\n", edge.vertexA, edge.vertexB, edge.weight);
        }

        // running time 출력
        System.out.println("Prim_RunningTime: " + (double) (end - start) / 1000000 + " ms");
    }

    public static List<Graph> PrimMST(List<Graph> graph) {
        int n = Num_Vartex(graph);
        int[] D = new int[n]; // 최소 가중치를 저장하는 배열
        int[] parent = new int[n]; // MST에서 각 정점이 최소 가중치를 가지는 짝
        boolean[] inMST = new boolean[n]; // MST에 포함 여부
        List<Graph> Tree = new ArrayList<>();

        Arrays.fill(D, Integer.MAX_VALUE); // 무한대로 초기화
        D[2] = 0; // 시작 정점의 가중치 0
        parent[2] = -1; // 시작 정점의 부모 없음

        for (int i = 0; i < n - 1; i++) { // 모든 정점을 MST에 포함할 때까지 반복
            int u = minVertex(D, inMST, n); // D 값이 최소인 정점 선택
            inMST[u] = true; // 선택한 정점을 MST에 포함

            //D업데이트
            for (Graph edge : graph) {
                int v = -1;
                int weight = edge.weight;

                if (edge.vertexA == u) {
                    v = edge.vertexB;
                }

                // v가 MST에 속하지 않고 가중치가 D[v]보다 작으면
                if (v != -1 && !inMST[v] && weight < D[v]) { 
                    D[v] = weight;
                    parent[v] = u;
                }
            }

            int vv = minVertex(D, inMST, n);
            Tree.add(new Graph(parent[vv], vv, D[vv]));
        }

        return Tree;
    }

    // 트리에 포함되어 있지 않고, D 값이 최소인 정점을 찾는 함수
    public static int minVertex(int[] D, boolean[] inMST, int n) {
        int min = Integer.MAX_VALUE, minIndex = -1;

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && D[v] < min) {
                min = D[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    // 그래프에서 정점의 개수를 자동으로 계산하는 함수
    public static int Num_Vartex(List<Graph> edges) {
        HashSet<Integer> vertices = new HashSet<>();
        for (Graph edge : edges) {
            vertices.add(edge.vertexA);
            vertices.add(edge.vertexB);
        }
        return vertices.size();
    }

    // 그래프의 간선을 정의하는 함수
    public static void generateGraph(List<Graph> edges) {
        addEdge(edges, 0, 1, 3);
        addEdge(edges, 0, 3, 2);
        addEdge(edges, 0, 4, 4);
        addEdge(edges, 1, 2, 1);
        addEdge(edges, 1, 3, 4);
        addEdge(edges, 1, 5, 2);
        addEdge(edges, 2, 5, 1);
        addEdge(edges, 3, 4, 5);
        addEdge(edges, 3, 5, 7);
        addEdge(edges, 4, 5, 9);
    }

    // 간선을 추가할 때 양방향으로 자동 추가하는 함수
    public static void addEdge(List<Graph> edges, int vertexA, int vertexB, int weight) {
        edges.add(new Graph(vertexA, vertexB, weight)); // 원래 방향
        edges.add(new Graph(vertexB, vertexA, weight)); // 반대 방향
    }
}

