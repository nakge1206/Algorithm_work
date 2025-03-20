import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Random;

public class quick_sort {
    public static void main(String[] args) throws Exception{
        try{
            //파일 읽고 배열에 저장
            String filename = "input_sort.txt";
            int count = 0;
            BufferedReader reader = new BufferedReader(new FileReader(filename));
            String line;
            while((line = reader.readLine()) != null){
                count++;
            }
            reader.close();
            int[] A = new int[count];
            reader = new BufferedReader(new FileReader(filename));
            int i=0;
            while((line = reader.readLine()) != null){
                A[i] = Integer.parseInt(line);
                i++;
            }
            reader.close();
            
            //running time 측정, QuickSort 시작
            long start = System.nanoTime(); 
            QuickSort(A,0, A.length-1);
            long end = System.nanoTime();

            //running time 출력
            System.out.println("Quick_RunningTime : " + (double)(end-start)/1000000 + " ms");

            //output파일 작성
            String outputFilename = "output_quick_sort.txt";
            BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilename));
            for (int a = 0; a < A.length; a++) {
                writer.write(Integer.toString(A[a]));
                writer.newLine();
            }
            writer.close();
        }catch (Exception e){
            System.out.println(e);
        }
    }

    public static void QuickSort(int[] A, int left, int right){
        if(left<right){
            //left~right에서 랜덤한 pivot 고르기
            Random random = new Random();
            int pivot = random.nextInt(right-left)+left;
            //pivot과 A[left] 자리 바꾸기
            swap(A, pivot, left);
            
            int small = left;
            int big = right;
            int pivot_value = A[left];
            while(big>small){
                while(big>=left+1 && A[big] >= pivot_value){
                    big--;
                }
                while(small<=right && A[small] <= pivot_value){
                    small++;
                }
                if(small < big){
                    swap(A, big, small);
                }
            }
            //pivot을 A[p]로 옮김
            swap(A, left, big);

            QuickSort(A, left, big-1);
            QuickSort(A, big+1, right);
        }

    }

    public static void swap(int[] A, int i, int j){
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}

