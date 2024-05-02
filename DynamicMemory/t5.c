#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define fn "t5.txt"
typedef struct word{
    char str[20];
    int num;
    struct word* next;
}WORD;

int main(){
    char s[20];
    FILE *fp;
    fp = fopen(fn,"r");
    
    WORD* head = (WORD*) malloc(sizeof(WORD));
    head->num = 1;
    head->next = NULL;
    fscanf(fp,"%s",head->str);
    while(fscanf(fp,"%s",s) != EOF){
        WORD* cur = head;
        while(cur != NULL){
            if(strcmp(cur->str,s) == 0 ){
                cur->num++;
                break;
            }
            else
                cur = cur->next;
        }
        if(cur == NULL){
            WORD* new_node =  (WORD*) malloc(sizeof(WORD));
            new_node->next = head->next;
            new_node->num = 1;
            strcpy(new_node->str,s);
            head->next = new_node;
        }
    }
    WORD* temp = head;
    while(head != NULL){
        temp = head;
        printf("%10s : %d times\n",temp->str,temp->num);
        head = head->next;
        free(temp);
    }
    fclose(fp);
    return 0;
}