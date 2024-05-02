#include "homework.h"

int main(){
    int next_round = 1;
    while(next_round == 1){

        printf("Please specify the input : ");
        scanf("%x",&input);

        printf("    Please specify the high : ");
        scanf("%d",&high);

        printf("    Please specify the low : ");
        scanf("%d",&low);

        printf("CheckRangeLow result : %d\n",CheckRangeLow(input,high,low));
        printf("CheckRangeNoLow result : %d\n",CheckRangeNoLow(input,high,low));
        printf("\n\n\n");
        
        printf("Enter 1 to keep trying the next round : ");
        scanf("%d",&next_round);
        
    }
    return 0;
}