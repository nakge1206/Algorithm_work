import java.io.*;
import java.util.*;

public class bubble{
    public static void main(String[] args) {
        String input_name = "input.txt";
        String output_name = "bubble_output.txt";

        try {
            Vector<Integer> A = new Vector<>();
            A.add(0); //의사코드에서 1~n-1까지라서 0번째는 안쓰는걸로 둠.
            try(BufferedReader br = new BufferedReader(new FileReader(input_name))){
                String line;
                while((line = br.readLine()) != null ) A.add(Integer.parseInt(line));
            }

            bubbleSort(A);

            try(BufferedWriter bw = new BufferedWriter(new FileWriter(output_name))){
                for(int i = 1; i<A.size(); i++){
                    bw.write(A.get(i) + "\n");
                }
            }
            System.out.println("정렬 및 출력(bubble_output.txt) 완료");
        } catch (IOException | NumberFormatException e) {
            System.err.println("에러 =  " + e.getMessage());
        }
    }

    public static void bubbleSort(Vector<Integer> A) {
        int n = A.size();
        for (int pass = 1; pass < n; pass++) {
            for (int i = 1; i <= n - pass; i++) {
                if (A.get(i-1) > A.get(i)) {
                    int temp = A.get(i-1);
                    A.set(i-1, A.get(i));
                    A.set(i, temp);
                }
            }
        }
    }
}