#include "homework.h"
int main(){
    int flag,i;
    int* buf =(int*) malloc(sizeof(int)*TOTAL);
    while(1){
        printf("Please enter (0) increasing or (1) decreasing sort : ");
        scanf("%d",&flag);
        if(flag != 0 && flag != 1){
            printf("ERROR: no such option!!!\n\n");
            continue;
        }
        printf("Please enter %d integers: ",TOTAL);
        for(i=0;i<TOTAL;i++)
            scanf("%d",&*(buf + i));
        if(flag == 0)
            BubbleSort(buf,CompInc);
        else if (flag == 1){
            BubbleSort(buf,CompDec);
        }
        PrintfSortedBuf(buf);
    }
    return 0;
}