import java.util.Arrays;

public class JobScheduling {

    public static void Approx_JobScheduling(int[] t, int m) {
        int[] L = new int[m];
        int[][] schedule = new int[m][100];

        Arrays.fill(L, 0);

        for (int i = 0; i < t.length; i++) {
            int min = 0;
            for (int j = 1; j < m; j++) {
                if (L[j] < L[min]) {
                    min = j;
                }
            }
            int start = L[min];
            int end = start + t[i];
            for (int time = start; time < end; time++) {
                schedule[min][time] = i + 1;
            }
            L[min] = end;
        }

        printSchedule(schedule, m, L);
    }

    public static void printSchedule(int[][] schedule, int m, int[] L) {
        int max = Arrays.stream(L).max().getAsInt();

        //t 정보
        System.out.print("m\\t"+"\t");
        for (int time = 0; time < max; time++) {
            System.out.print(time + "\t");
        }
        System.out.println();

        for (int i = m - 1; i >= 0; i--) {
            System.out.print((i + 1) + "\t");
            for (int time = 0; time < max; time++) {
                if (schedule[i][time] == 0) {
                    System.out.print("\t");
                } else {
                    System.out.print("t" + schedule[i][time] + "\t");
                }
            }
            System.out.println();
        }
        System.out.println("\n종료시각 : " + maxTime);
    }

    public static void main(String[] args) {
        int[] t = {5, 2, 4, 3, 4, 7, 9, 2, 4, 1};
        int m = 4;

        Approx_JobScheduling(t, m);
    }
}