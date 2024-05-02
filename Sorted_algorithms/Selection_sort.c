#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 30
void swap(int* a,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;

}

void selection_sort(int* A){
    int min_idx;
    printf("\n");
    for(int i = 0;i < n;i++){
        min_idx = i;
        for(int j = i+1;j < n;j++)
            min_idx = (A[min_idx] < A[j]) ? min_idx:j;
        swap(&A[i],&A[min_idx]);
    }

}
int main(){
    int i,A[n];
    srand(time(NULL));
    
    for(i = 0;i < n;i++) A[i] = rand() % 100;
    printf("before\n");
    for(i = 0;i < n;i++) printf(" %d",A[i]);
  
    selection_sort(A);
    
    printf("\nAfter\n");
    for(i = 0;i < n;i++) printf(" %d",A[i]);
    printf("\n");
    return 0;
}