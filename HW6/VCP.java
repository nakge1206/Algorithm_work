import java.util.*;

public class VCP {
    static class Edge {
        String u, v;

        Edge(String u, String v) {
            this.u = u;
            this.v = v;
        }

        @Override
        public String toString() {
            return u + "-" + v;
        }
    }

    public static void main(String[] args) {
        // 그래프의 인접 리스트 정의
        Map<String, List<String>> graph = new HashMap<>();

        // 노드와 엣지 추가
        String[] nodes = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};
        for (String node : nodes) {
            graph.put(node, new ArrayList<>());
        }

        addEdge(graph, "A", "B");
        addEdge(graph, "A", "E");
        addEdge(graph, "B", "C");
        addEdge(graph, "B", "E");
        addEdge(graph, "B", "G");
        addEdge(graph, "B", "F");
        addEdge(graph, "C", "D");
        addEdge(graph, "C", "G");
        addEdge(graph, "D", "H");
        addEdge(graph, "D", "G");
        addEdge(graph, "E", "F");
        addEdge(graph, "E", "I");
        addEdge(graph, "E", "J");
        addEdge(graph, "F", "G");
        addEdge(graph, "F", "J");
        addEdge(graph, "G", "H");
        addEdge(graph, "G", "J");
        addEdge(graph, "G", "K");
        addEdge(graph, "G", "L");
        addEdge(graph, "H", "L");
        addEdge(graph, "I", "J");
        addEdge(graph, "J", "K");
        addEdge(graph, "J", "O");
        addEdge(graph, "I", "M");
        addEdge(graph, "J", "N");
        addEdge(graph, "J", "M");
        addEdge(graph, "K", "L");
        addEdge(graph, "K", "O");
        addEdge(graph, "L", "P");
        addEdge(graph, "L", "O");
        addEdge(graph, "M", "N");
        addEdge(graph, "N", "O");
        addEdge(graph, "O", "P");

        // 최대 매칭 찾기
        Set<Edge> matching = VCP(graph);

        // 출력
        System.out.println("Maximal Matching Edges:");
        for (Edge edge : matching) {
            System.out.println(edge);
        }
    }

    private static void addEdge(Map<String, List<String>> graph, String u, String v) {
        graph.get(u).add(v);
        graph.get(v).add(u);
    }

    private static Set<Edge> VCP(Map<String, List<String>> graph) {
        Set<Edge> matching = new HashSet<>();
        Set<String> visited = new HashSet<>();

        for (String u : graph.keySet()) {
            if (!visited.contains(u)) {
                for (String v : graph.get(u)) {
                    if (!visited.contains(v)) {
                        // Edge (u, v)를 매칭에 추가
                        matching.add(new Edge(u, v));
                        visited.add(u);
                        visited.add(v);
                        break; // 현재 노드(u)에 대해 더 이상 매칭을 찾지 않음
                    }
                }
            }
        }

        return matching;
    }
}


