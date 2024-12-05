import java.util.*;

public class VertexCover {
    // 정점을 나타내는 클래스
    static class Edge {
        int u, v;

        Edge(int u, int v) {
            this.u = u;
            this.v = v;
        }

        @Override
        public String toString() {
            return "(" + u + ", " + v + ")";
        }
    }

    public static Set<Edge> maximalMatching(Set<Edge> edges, int numVertices) {
        Set<Edge> matching = new HashSet<>();
        Set<Integer> visited = new HashSet<>();

        // 간선을 순회하며 매칭 생성
        for (Edge edge : edges) {
            if (!visited.contains(edge.u) && !visited.contains(edge.v)) {
                matching.add(edge);
                visited.add(edge.u);
                visited.add(edge.v);
            }
        }
        return matching;
    }

    public static void main(String[] args) {
        // 그래프의 정점 (16개 정점: 1~16)
        int numVertices = 16;
        // 숫자 -> 알파벳 매핑
        Map<Integer, Character> numToAlpha = new HashMap<>();
        for (int i = 1; i <= 16; i++) {
            numToAlpha.put(i, (char) ('A' + i - 1));
        }

        // 간선의 집합
        Set<Edge> edges = new HashSet<>();
        edges.add(new Edge(1, 2));
        edges.add(new Edge(1, 5));
        edges.add(new Edge(2, 3));
        edges.add(new Edge(2, 5));
        edges.add(new Edge(2, 6));
        edges.add(new Edge(2, 7));
        edges.add(new Edge(3, 4));
        edges.add(new Edge(3, 7));
        edges.add(new Edge(4, 7));
        edges.add(new Edge(4, 8));
        edges.add(new Edge(5, 6));
        edges.add(new Edge(5, 9));
        edges.add(new Edge(5, 10));
        edges.add(new Edge(6, 7));
        edges.add(new Edge(6, 10));
        edges.add(new Edge(7, 8));
        edges.add(new Edge(7, 10)); 
        edges.add(new Edge(7, 11));
        edges.add(new Edge(7, 12));
        edges.add(new Edge(8, 12));
        edges.add(new Edge(9, 10));
        edges.add(new Edge(9, 13));
        edges.add(new Edge(10, 11));
        edges.add(new Edge(10, 13));
        edges.add(new Edge(10, 14));
        edges.add(new Edge(10, 15));
        edges.add(new Edge(11, 12));
        edges.add(new Edge(11, 15));
        edges.add(new Edge(12, 15));
        edges.add(new Edge(12, 16));
        edges.add(new Edge(13, 14));
        edges.add(new Edge(14, 15));
        edges.add(new Edge(15, 16));

        // Maximal Matching을 이용하여 간선 선택
        Set<Edge> result = maximalMatching(edges, numVertices);

        // 결과 출력
        System.out.println("Maximal Matching Edges:");
        for (Edge edge : result) {
            char u = numToAlpha.get(edge.u);
            char v = numToAlpha.get(edge.v);
            System.out.println("(" + u + ", " + v + ")");
        }
    }
}