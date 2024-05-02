#include<stdio.h>
#include<stdlib.h>

typedef struct num_storage{
    int number;
    struct num_storage* next;
}tNumStorage;

typedef struct num_stor_head{
        int counts;
        struct num_storage* head;
        struct num_storage* tail;
}tNumstorHead;

void initial_list(tNumstorHead* list);
void get_input(tNumstorHead* list);
void print_list(tNumstorHead* list);
void sort_list(tNumstorHead* list,int input);

int main(){
    tNumstorHead* list;
    list = (tNumstorHead*) malloc(sizeof(tNumstorHead));
    initial_list(list);
    get_input(list);
    return 0;
}
void initial_list(tNumstorHead* list){
    list->counts = 0;
    list->head  = NULL;
    list->tail  = NULL;
}
void print_list(tNumstorHead* list){
    tNumStorage* node_ptr;
    node_ptr = list->head;
    printf("  The sorted list: ");
    while(node_ptr != NULL){
        printf("%d ",node_ptr->number);
        node_ptr = node_ptr->next;
    }
    printf("\n\n");
}
void get_input(tNumstorHead* list){
    int number;
    while(1){
        printf("Input a number  : ");
        scanf("%d",&number);
        if(number == -1){
             break;
        }
        else{
            sort_list(list,number);
            list->counts ++;
            printf("  list->counts: %d\n",list->counts);
            print_list(list);
        }
    }
}
void sort_list(tNumstorHead* list,int input){
    tNumStorage* new_list_ptr;
    tNumStorage* node_ptr;
    new_list_ptr = (tNumStorage*) malloc(sizeof(tNumStorage));
    new_list_ptr->number = input;
    if(list->counts == 0){
        list->head = new_list_ptr;
        list->tail = new_list_ptr;
    }
    else{
        node_ptr = list->head;
        if(node_ptr->number >= input){
            new_list_ptr->next = list->head;
            list->head = new_list_ptr; 
        }
        else{
            while(node_ptr->next != NULL){
                if(node_ptr->next->number >= input){
                    new_list_ptr->next = node_ptr->next;
                    node_ptr->next = new_list_ptr;
                    return;
                }
                node_ptr = node_ptr->next; 
            }
            node_ptr->next = new_list_ptr;
            new_list_ptr->next = NULL;
            list->tail = new_list_ptr;
        }
    }    
}
