#include<stdio.h>
#include<stdlib.h>

int main(){
    char* p;
    int m = 1;
    while((p = (char*) malloc(m*1024*sizeof(char))) != NULL){
        if(p) m++;
        free(p);
    }
    printf("Memory has already allocated : %d K\n", m);
}