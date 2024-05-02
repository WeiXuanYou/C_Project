#include<stdio.h>
#include<stdlib.h>

int main(){
    int** ta;
    int a,b,i,j;
    printf("How many arrays do you want? :");
    scanf("%d %d",&a,&b);
    printf("a = %d, b = %d\n",a,b); 
    ta = (int**)  calloc(a,sizeof(int*));
    for(i = 0;i < b;i++)
        *(ta+i) = (int*) malloc(sizeof(int));

    for(i = 0;i < a;i++){
        for(j = 0;j < b;j++){
            *(*(ta+i)+j) = i+j;
            printf("%2d ",*(*(ta+i)+j));
        }
        printf("\n");
    }
    free(ta);
} 