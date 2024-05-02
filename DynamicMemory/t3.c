#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int i = 0,j = 0;
    char s1[80],s2[80],*p;
    fgets(s1,80,stdin);
    fgets(s2,80,stdin);
    p = (char*) malloc((strlen(s1)+ strlen(s2) +1)*sizeof(char));
    while(s1[i]){
        p[i] = s1[i];
        i++;
    }
    while(s2[j]){
        p[i+j] = s2[j];
        j++;
    }
    p[i+j] = '\0';
    puts(p);
    free(p);
    return 0;
}