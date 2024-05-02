#include<stdio.h>
#include<stdlib.h>
#define fn t7.c

int main(){
    char *p;
    p = (char*) malloc(sizeof(char)*20);
    fgets(p,20,stdin);
    puts(p);
    
    free(p);

    return 0;
}