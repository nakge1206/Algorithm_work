import java.util.*;

public class SetCover {

    static List<Integer> universalSet = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    static Map<String, List<Integer>> subsets = new LinkedHashMap<>();
    static {
        subsets.put("S1", Arrays.asList(1, 2, 3, 8));
        subsets.put("S2", Arrays.asList(1, 2, 3, 4, 8));
        subsets.put("S3", Arrays.asList(1, 2, 3, 4));
        subsets.put("S4", Arrays.asList(2, 3, 4, 5, 7, 8));
        subsets.put("S5", Arrays.asList(4, 5, 6, 7));
        subsets.put("S6", Arrays.asList(5, 6, 7, 9, 10));
        subsets.put("S7", Arrays.asList(4, 5, 6, 7));
        subsets.put("S8", Arrays.asList(1, 2, 4, 8));
        subsets.put("S9", Arrays.asList(6, 9));
        subsets.put("S10", Arrays.asList(6, 10));
    }

    public static List<String> Setcover(List<Integer> U, Map<String, List<Integer>> F) {
        List<String> C = new ArrayList<>(); 
        List<Integer> uncovered = new ArrayList<>(U); 
        while (!uncovered.isEmpty()) {
            String bestSubset = null;
            int maxCovered = 0;

            // 가장 많은 원소를 커버하는 부분 집합 찾기
            for (Map.Entry<String, List<Integer>> entry : F.entrySet()) {
                List<Integer> subset = entry.getValue();
                int coveredCount = 0;

                for (int elem : subset) {
                    if (uncovered.contains(elem)) {
                        coveredCount++;
                    }
                }

                if (coveredCount > maxCovered) {
                    bestSubset = entry.getKey();
                    maxCovered = coveredCount;
                }
            }

            if (bestSubset == null) {
                break; 
            }

            C.add(bestSubset);
            uncovered.removeAll(F.get(bestSubset));
            F.remove(bestSubset);
        }

        return C;
    }

    public static Set<String> optimalSetcover(List<Integer> U, Map<String, List<Integer>> F) {
        Set<String> bestCover = null;

        List<String> subsetsList = new ArrayList<>(F.keySet());
        int n = subsetsList.size();
        int powerSetSize = 1 << n;

        for (int i = 1; i < powerSetSize; i++) {
            Set<String> cover = new HashSet<>();
            Set<Integer> covered = new HashSet<>();

            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) > 0) {
                    String subsetName = subsetsList.get(j);
                    cover.add(subsetName);
                    covered.addAll(F.get(subsetName));
                }
            }

            if (covered.containsAll(U) && (bestCover == null || cover.size() < bestCover.size())) {
                bestCover = new HashSet<>(cover);
            }
        }
        return bestCover;
    }

    public static void main(String[] args) {
        long startTime = System.nanoTime();
        List<String> cover = Setcover(universalSet, new LinkedHashMap<>(subsets));
        long endTime = System.nanoTime();

        System.out.println("C : " + cover);
        System.out.println("Running Time: " + (endTime - startTime) / 1e6 + " ms");

        startTime = System.nanoTime();
        Set<String> optimalCover = optimalSetcover(universalSet, subsets);
        endTime = System.nanoTime();
        double optimalTime = (endTime - startTime) / 1e6;

        System.out.println("\nOptimal Set Cover: " + optimalCover);
        System.out.println("Optimal Algorithm Running Time: " + optimalTime + " ms");

    }
}

