import java.util.*;

public class VertexCover {
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
        Map<String, List<String>> graph = new HashMap<>();

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

        Set<Edge> max_matching = vertex_cover(graph);

        System.out.println("극대 매칭 간선 : ");
        for (Edge edge : max_matching) {
            System.out.println(edge);
        }
    }

    private static void addEdge(Map<String, List<String>> graph, String u, String v) {
        graph.get(u).add(v);
        graph.get(v).add(u);
    }

    private static Set<Edge> vertex_cover(Map<String, List<String>> graph) {
        Set<Edge> matching = new HashSet<>();
        Set<String> visited = new HashSet<>();

        for (String u : graph.keySet()) {
            if (!visited.contains(u)) {
                for (String v : graph.get(u)) {
                    if (!visited.contains(v)) {
                        matching.add(new Edge(u, v));
                        visited.add(u);
                        visited.add(v);
                        break;
                    }
                }
            }
        }

        return matching;
    }
}


