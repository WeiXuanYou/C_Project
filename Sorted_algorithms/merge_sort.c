#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 10

int temp[n];

void Merge(int* A,int left,int right){
    int i = left;
    int j = (left + right)/2 + 1;
    int k = left;

    while( i <= (left + right)/2 && j <= right){
        if(A[i] <= A[j]){
            temp[k] = A[i]; 
            i++;
        }
        else{
            temp[k] = A[j];
            j++;
        }
        k++;
    }
    if(i <= (left + right)/2){
        for(int l = 0;l <= (left + right) / 2 - i;l++)
            temp[k + l] = A[i+l];
    }
    else{
        for(int l = 0;l <= right - j;l++)
            temp[k + l] = A[j + l];
    }

    for(int l = left;l <= right;l++)
        A[l] = temp[l];
}


void MergeSort(int* A,int left,int right){
    if(right > left){
        int mid = (left + right) /2;
        MergeSort(A,left,mid);
        MergeSort(A,mid + 1,right);
        Merge(A,left,right);
    }
}

int main(){
    int A[n];
    srand(time(NULL));
    for(int i = 0; i < n; i++) A[i] = rand() % 100;
    for(int i = 0; i < n; i++) printf(" %d",A[i]);

    MergeSort(A,0,n-1);

    printf("\n");
    for(int i = 0; i < n; i++) printf(" %d",A[i]);
    printf("\nDone");
    printf("\n");
    return 0;    
}