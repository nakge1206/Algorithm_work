public class EditDistance {
    public static int[][] editDistance(String S, String T) {
        int m = S.length();
        int n = T.length();

        int[][] E = new int[m+1][n+1];

        for (int i = 0; i <= m; i++) {
            E[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            E[0][j] = j;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int cost = (S.charAt(i - 1) == T.charAt(j - 1)) ? 0 : 1; // 강의내용 알파
                E[i][j] = Math.min(E[i - 1][j] + 1, // 삭제
                        Math.min(E[i][j - 1] + 1, // 삽입
                                E[i - 1][j - 1] + cost)); // 대체
            }
        }

        return E;
    }

    public static void printE(String S, String T, int[][] E) {
        int m = S.length();
        int n = T.length();

        System.out.print("    ε ");
        for (int j = 0; j < n; j++) {
            System.out.print(T.charAt(j) + " ");
        }
        System.out.println();

        System.out.print("  - ");
        for (int j = 0; j <= n; j++) {
            System.out.print(j + " ");
        }
        System.out.println();

        for (int i = 0; i <= m; i++) {
            if (i == 0) {
                System.out.print("ε 0 ");
            } else {
                System.out.print(S.charAt(i - 1) + " " + i + " ");
            }

            System.out.print(E[i][0] + " ");
            for (int j = 1; j <= n; j++) {
                System.out.print(E[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        String S = "strong";
        String T = "stone";

        int[][] E = editDistance(S, T);

        System.out.println("Edit Distance Table:");
        printE(S, T, E);
    }
}