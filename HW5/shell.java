import java.io.*;
import java.util.*;

public class shell {
    public static void main(String[] args) {
        String input_name = "input.txt";
        String output_name = "shell_output.txt";

        try {
            Vector<Integer> A = new Vector<>();
            try (BufferedReader br = new BufferedReader(new FileReader(input_name))) {
                String line;
                while ((line = br.readLine()) != null) A.add(Integer.parseInt(line.trim()));
            }

            shellSort(A);

            try (BufferedWriter bw = new BufferedWriter(new FileWriter(output_name))) {
                for(int i = 1; i<A.size(); i++){
                    bw.write(A.get(i) + "\n");
                }
            }

            System.out.println("정렬 및 출력(shell_output.txt) 완료");
        } catch (IOException | NumberFormatException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static void shellSort(Vector<Integer> A) {
        int n = A.size();
        int[] gap = {100, 50, 10, 5, 1}; 
        
        for(int h = 0; h<gap.length; h++){
            for (int i = h; i < n; i++) {
                int CurrentElement = A.get(i);
                int j = i;

                while (j >= h && A.get(j - h) > CurrentElement) {
                    A.set(j, A.get(j - h));
                    j -= h;
                }
                A.set(j, CurrentElement);
            }
        }
    }
}