#include<stdio.h>
#include<stdlib.h>

#define Cutoff (3)

int tmp;

void print(int *A, int len){
    for(int i = 0; i <len; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

/* (a) Shell Sort using the increments {1, 3, 7} */
void increment_insertion_sort(int *A, int increment, int length);
void shell_sort(int *A, int length){
    int H[7] = {7, 3, 1};
    for(int i = 0; i < 3; i ++){
        increment_insertion_sort(A, H[i], length);
    }
}

void increment_insertion_sort(int *A, int increment, int length){
    int i, j, p;
    for(i = 0; i < increment; ++i){
        for(p = i + increment; p < length; p = p + increment){
            tmp = A[p];
            j = p;
            while(j >= increment && A[j - increment] > tmp){
                A[j] = A[j - increment];
                j = j - increment;
            }
            A[j] = tmp;
        }
    }
}

/* (b) Merge Sort */
void Merge(int *A, int *TempArr, int l_p, int r_p, int r_end);
void MSort(int *A, int *TempArr, int left, int right);
void merge_sort(int *A, int length){
    int *TempArr;
    TempArr = malloc(length * sizeof(int));
    if(TempArr != NULL){
        MSort(A, TempArr, 0, length - 1);
        free(TempArr);
    }
    else{
        printf("No space for merge sort :( \n");
    }
}

void MSort(int *A, int *TempArr, int left, int right){
    int center;
    if(left < right){
        center = (left + right) / 2;
        MSort(A, TempArr, left, center);
        MSort(A, TempArr, center + 1, right);
        Merge(A, TempArr, left, center + 1, right);
    }
}

void Merge(int *A, int *TempArr, int l_p, int r_p, int r_end){
    int i = 0, j = 0, k = 0;
    while(i < (r_p - l_p) && j < (r_end - r_p + 1)){
        if (A[i] < A[j]){
            TempArr[k] = A[i];
            i++;
        }
        else{
            TempArr[k] = A[j];
            j++;
        }
        k++;
    }
    while(i < (r_p - l_p)){
        TempArr[k++] = A[i++];
    }
    while(j < (r_end - r_p + 1)){
        TempArr[k++] = A[j++];
    }
}

/* (c) Quick Sort with median-of-three pivot selection, the partitioning strategy and a cut-off of 3 (along with the Insertion Sort) */
int FindPivot(int *A, int l_end, int r_end);
void Partition(int *A, int left, int right);
void quick_sort(int *A, int length){
    Partition(A, 0, length - 1);
}

void Partition(int *A, int left, int right){
    if(left + Cutoff <= right){
        int pivot = FindPivot(A, left, right);
        int i = left, j = right - 1;
        for( ; ;){
            while(A[++i] < pivot) {};
            while(A[--j] > pivot) {};
            if(i < j){
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
            else break;
        }
        tmp = A[i];
        A[i] = A[right - 1];
        A[right - 1] = tmp;
        Partition(A, left, i - 1);
        Partition(A, i + 1, right);
    }
    increment_insertion_sort(A, 1, right - left + 1);
}

int FindPivot(int *A, int l_end, int r_end){
    int center = (l_end + r_end) / 2;
    if(A[l_end] > A[center]){
        tmp = A[l_end];
        A[l_end] = A[center];
        A[center] = tmp;
    }
    if(A[l_end] > A[r_end]){
        tmp = A[l_end];
        A[l_end] = A[r_end];
        A[r_end] = tmp;
    }
    if(A[center] > A[r_end]){
        tmp = A[center];
        A[center] = A[r_end];
        A[r_end] = tmp;
    }
    tmp = A[center];
    A[center] = A[r_end - 1];
    A[r_end - 1] = tmp;
    return A[r_end - 1];
}

int main(){
    int *A;
    int data, len; 
    char ch; 
    printf("Please input a sequence of integers (at most 100 integers) separated with space: \n");
    do{
        A[len] = (int)malloc(sizeof(int));
        scanf("%d", &data);
        A[len++] = data;
    } while((ch = getchar()) != '\n');

    if(len > 100){
        printf("Your list is limited to contain 100 numbers :( ");
        len = 100;
    }
    printf("\n");

    printf("(a) shell sort output: \n");
    shell_sort(A, len);
    print(A, len);

    printf("(b) merge sort output: \n");
    merge_sort(A, len);
    print(A, len);

    printf("(c) quick sort output: \n");
    quick_sort(A, len);
    print(A, len);

    return 0;
}

