#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 10
void swap(int* a,int* b){
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}
int partting(int* A,int left,int right){
    int i = left;
    int j = right;
    while(i < j){
        while(A[left] > A[++i]);
        while(A[left] < A[--j]);
        if(i < j) swap(&A[i],&A[j]);
    }
    swap(&A[left],&A[j]);
    return j;
}
void quick_sort(int* A,int left,int right){
    int p;
    if(left < right){
        p = partting(A,left,right + 1);
        quick_sort(A,left,p - 1);
        quick_sort(A,p + 1,right);
    }
}

int main(){
    int A[n];
    srand(time(NULL));
    for(int i = 0;i<n;i++) A[i] = rand() % 100; 
    for(int i = 0;i<n;i++) printf(" %d",A[i]);
    printf("\n");

    quick_sort(A,0,n-1);

 
    for(int i = 0;i < n;i++) printf(" %d",A[i]);
    
    printf("\n");
    return 0;
}