#include<stdio.h>
#include<stdlib.h>

int f(int n,int* arr){
    if(n == 0 | n == 1){
        arr[n] = 1;
        return 1;
    }
    arr[n] = f(n-1,arr) + f(n-2,arr);
    return arr[n];
}

int main(){
    int n = 10;
    int* arr = (int*) malloc(n*sizeof(int));
    for(int i = 0;i < n;i++){
        *(arr + i) = 0;
    }
    f(n-1,arr);
    for(int i=0;i<n;i++)
        printf("%d\n",arr[i]);
  
}