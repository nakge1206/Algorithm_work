import java.util.*;

class BranchAndBound {
    static int N; // 도시 수
    static int best_cost = Integer.MAX_VALUE; //최적가중치
    static List<String> best_solution = new ArrayList<>(); //최적경로
    static List<String> cities = new ArrayList<>(); //도시 이름 저장함.
    static Map<String, Map<String, Integer>> graph = new HashMap<>(); //자료예제에 있는 양방향 그래프

    public static void main(String[] args) {
        //양방향 그래프 구현
        addEdge("A", "B", 2);
        addEdge("A", "C", 7);
        addEdge("A", "D", 3);
        addEdge("A", "E", 10);
        addEdge("B", "C", 3);
        addEdge("B", "D", 5);
        addEdge("B", "E", 4);
        addEdge("C", "D", 6);
        addEdge("C", "E", 1);
        addEdge("D", "E", 9);

        //도시이름 리스트 추가
        cities = new ArrayList<>(graph.keySet());
        N = cities.size();

        //간선을 테이블로 구현
        int[][] table = create_table();

        //Branch-and-Bound 실행
        branchAndBound(table);

        //최적값 출력
        System.out.print(best_solution);
        System.out.println(" 거리: " + best_cost);
    }

    //Branch And Bound 구현
    private static void branchAndBound(int[][] table) {
        //한정값으로 정렬하는 큐 생성(activeNodes)
        PriorityQueue<Node> activeNodes = new PriorityQueue<>(Comparator.comparingInt(n -> n.bound));
        boolean[] visited = new boolean[N]; //방문 여부
        visited[0] = true; //A부터 시작

        //초기 노드 추가
        Node root = new Node(0, 0, calculateBound(table, visited, new ArrayList<>(List.of(cities.get(0)))), new ArrayList<>(List.of(cities.get(0))), visited);
        //활성화노드에 시작점 추가
        activeNodes.add(root);

        while (!activeNodes.isEmpty()) {
            Node current = activeNodes.poll(); // 한정값이 가장 낮은 노드 선택

            // 가지치기
            if (current.bound >= best_cost) {
                continue;
            }

            // 완전한 해라면
            if (current.path.size() == N) {
                //시작점 가는 cost 추가
                int final_cost = current.cost + table[current.vertex][0];
                if (final_cost < best_cost) {
                    best_cost = final_cost;
                    best_solution = new ArrayList<>(current.path);
                    best_solution.add(cities.get(0)); // 시작점 추가
                }
                continue;
            }

            // 자식 노드 확장
            for (int i = 0; i < N; i++) {
                if (!current.visited[i]) {
                    boolean[] newVisited = Arrays.copyOf(current.visited, N);
                    newVisited[i] = true;

                    List<String> newPath = new ArrayList<>(current.path);
                    newPath.add(cities.get(i));

                    int newCost = current.cost + table[current.vertex][i];
                    int newBound = calculateBound(table, newVisited, newPath);

                    //가지치기 부분
                    if (newBound < best_cost) {
                        activeNodes.add(new Node(i, newCost, newBound, newPath, newVisited));
                    }
                }
            }
        }
    }

    private static int calculateBound(int[][] table, boolean[] visited, List<String> path) {
        int bound = 0;
        int[] count = new int[N]; // 각 도시의 경로 사용 횟수
        
        //확실한 경로가 있는 경우 한정값에 경로를 두번 더한뒤, 각각의 count를 더함.
        for (int i = 0; i < path.size() - 1; i++) {
            String currCity = path.get(i);
            String nextCity = path.get(i + 1);
    
            int currIndex = cities.indexOf(currCity);
            int nextIndex = cities.indexOf(nextCity);
    
            bound += table[currIndex][nextIndex];
            bound += table[currIndex][nextIndex];
            
            count[currIndex]++;
            count[nextIndex]++;
    
        }
    
        for (int i = 0; i < N; i++) {
            if (count[i] == 1) { // 확정된 경로로 한 번 사용된 도시
                int minCost = Integer.MAX_VALUE;
    
                //직접 연결 안되어 있으면 한정값 구할때 상관없음.
                for (int j = 0; j < N; j++) {
                    if (i != j && !isConnected(i, j, path)) {
                        minCost = Math.min(minCost, table[i][j]);
                    }
                }
    
                if (minCost != Integer.MAX_VALUE) {
                    bound += minCost;
                }
            } else if (count[i] == 0) { // 방문하지 않은 도시
                int min1 = Integer.MAX_VALUE, min2 = Integer.MAX_VALUE;
                for (int j = 0; j < N; j++) {
                    if (i != j) {
                        if (table[i][j] < min1) {
                            min2 = min1;
                            min1 = table[i][j];
                        } else if (table[i][j] < min2) {
                            min2 = table[i][j];
                        }
                    }
                }
                bound += min1 + min2;
            }
        }
    
        //한정값 반으로 나누고, 소수점 있으면 올리기
        bound = (int) Math.round(bound / 2.0);
        return bound;
    }
    
    //직접 연결되어있는지 확인하는 함수(직접 연결되어있으면 true, 아니면 false)
    private static boolean isConnected(int cityIndex, int targetIndex, List<String> path) {
        String city = cities.get(cityIndex);
        String target = cities.get(targetIndex);
    
        for (int i = 0; i < path.size() - 1; i++) {
            String currCity = path.get(i);
            String nextCity = path.get(i + 1);
    
            if ((currCity.equals(city) && nextCity.equals(target)) ||
                (currCity.equals(target) && nextCity.equals(city))) {
                return true;
            }
        }
        return false;
    }

    //양방향 그래프 구현함.
    private static void addEdge(String from, String to, int cost) {
        graph.putIfAbsent(from, new HashMap<>());
        graph.putIfAbsent(to, new HashMap<>());
        graph.get(from).put(to, cost);
        graph.get(to).put(from, cost);
    }

    //그래프를 테이블(2차원 배열)로 구현
    private static int[][] create_table() {
        int[][] table = new int[N][N];
        for (int i = 0; i < N; i++) {
            Arrays.fill(table[i], Integer.MAX_VALUE);
            for (int j = 0; j < N; j++) {
                if (i == j) table[i][j] = 0;
                else {
                    String from = cities.get(i);
                    String to = cities.get(j);
                    if (graph.get(from).containsKey(to)) {
                        table[i][j] = graph.get(from).get(to);
                    }
                }
            }
        }
        return table;
    }

    //정점, 가중치, 한정값, 경로, 방문여부를 담은 Node 클래스 정의
    static class Node {
        int vertex, cost, bound;
        List<String> path;
        boolean[] visited;

        Node(int vertex, int cost, int bound, List<String> path, boolean[] visited) {
            this.vertex = vertex;
            this.cost = cost;
            this.bound = bound;
            this.path = path;
            this.visited = visited;
        }
    }
}