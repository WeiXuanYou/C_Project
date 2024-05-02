#include "function.h"
int CompInc(int x,int y){
    return x < y;
}
int CompDec(int x,int y){
    return x > y;
}
void BubbleSort(int* buf,int (*callbackfun)(int,int)){
    int i,j;
    //int (*SortNum[2])(int,int) = {CompInc,CompDec};

    for(i = 1;i < TOTAL;i++){
        for(j = 0;j<TOTAL-i;j++){
            if(callbackfun(*(buf+j+1),*(buf+j))){
                *(buf + j + 1) ^= *(buf + j);
                *(buf + j) ^= *(buf + j + 1);
                *(buf + j + 1) ^= *(buf + j);
            }
        }
    }
}
void PrintfSortedBuf(int* buf){
    printf("Sorted numbers : ");
    for(int i=0;i<TOTAL;i++){
        printf("%d ",*(buf+i));
    }
    printf("\n\n");
}
