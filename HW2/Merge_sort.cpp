#include <iostream>
#include <fstream>
#include <numeric>
#include <time.h>
using namespace std;

void Merge(int *A, int start, int end, int middle){
    int *newA = new int[end-start+1];
    int p = start;
    int k = middle+1;
    int i = 0;

    while(p<=middle && k<=end){
        if(A[p]<=A[k]) newA[i++] = A[p++];
        else newA[i++] = A[k++];
    }

    if(p>middle){
        while(k<=end) newA[i++] = A[k++];
    }else{
        while(p<=middle) newA[i++] = A[p++];
    }

    for(int a = start, b = 0; a<=end; a++,b++) A[a]=newA[b];
}

void MergeSort(int *A, int p, int q){
    if(p<q){
        int k = (p+q)/2;
        MergeSort(A,p,k);
        MergeSort(A,k+1,q);
        Merge(A,p, q, k);
    }

}

int main() {
    //input 파일 읽고 Array 저장
    ifstream fin("input_sort.txt");
    if (!fin.is_open()) {
        cout << "open error" << endl;
        return 1;
    }
    int count = 0, temp;
    while (fin >> temp) count++;
    fin.clear();
    fin.seekg(0, ios::beg);
    int* Array = new int[count];
    for (int i = 0; i < count; i++) fin >> Array[i];
    fin.close();

    //running time 측정, MergeSort 시작 
    clock_t start, end;
    start = clock();
    MergeSort(Array, 0, count-1);
    end = clock();

    //running time 출력
    cout << "Merge_RunningTime : " << (double)(end-start) << " ms" << "\n" << endl;


    //output파일 작성 및 메모리반환
    ofstream fout("output_merge_sort.txt");
    if (!fout.is_open()) {
        cout << "open error" << endl;
        return 1;
    }
    for(int i=0; i<count;i++) fout << Array[i] << endl;
    fout.close();
    delete[] Array;

    return 0;
}

