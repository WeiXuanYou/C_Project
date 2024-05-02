#include"list.h"

void initial_list(tNumstorHead* list){
    list->counts = 0;
    list->head  = NULL;
    list->tail  = NULL;
}

void print_list(tNumstorHead* list){
    tNumStorage* node_ptr;
    node_ptr = list->head;
    printf("   From head --> ");
    while(node_ptr != NULL){
        printf("%d ",node_ptr->number);
        node_ptr = node_ptr->next;
    }

    printf("\n   From tail --> ");
    node_ptr = list->tail; 
    while(node_ptr != NULL){
        printf("%d ",node_ptr->number);
        node_ptr = node_ptr->pre_node;
    }
    printf("\n\n");
}
void add_node(tNumstorHead *list,int add_num,int target_location,int before_or_after){
    int i;
    tNumStorage* new_list_ptr;
    tNumStorage* node_ptr;
    new_list_ptr = (tNumStorage*) malloc(sizeof(tNumStorage));
    new_list_ptr->number = add_num;

    if(list->counts == 0){
        list->head = new_list_ptr;
        list->tail = new_list_ptr;
    }
    else{
        node_ptr = list->head;
        if(before_or_after == 1 && list->counts==1){
            new_list_ptr->next = node_ptr;
            node_ptr->pre_node = new_list_ptr;
            new_list_ptr->pre_node = NULL;
            list -> head = new_list_ptr;
        }
        else{
            if(list->counts == target_location && before_or_after == 2){
                node_ptr = list->tail;
                list->tail->next = new_list_ptr;
                new_list_ptr->pre_node = list->tail;
                new_list_ptr->next = NULL;
                list->tail = new_list_ptr;
            }
            else{
                for(i=1;i <= list->counts;i++){
                    if(target_location == i){
                        if(before_or_after == 1){
                            if(i==1){
                                new_list_ptr->pre_node = NULL;
                                new_list_ptr->next = node_ptr;
                                node_ptr->pre_node = new_list_ptr;
                                list->head = new_list_ptr;
                            }
                            else{
                                new_list_ptr->pre_node = node_ptr->pre_node;
                                new_list_ptr->next = node_ptr;
                                node_ptr->pre_node->next = new_list_ptr ;
                                node_ptr->pre_node = new_list_ptr;
                            }
                            return;
                        }
                        else{
                            new_list_ptr->next = node_ptr->next;
                            new_list_ptr->pre_node = node_ptr;
                            node_ptr->next->pre_node = new_list_ptr;
                            node_ptr->next = new_list_ptr;
                            return;
                        }
                    }
                    node_ptr = node_ptr->next;
                }
            }
        }
    }
}

void delete(tNumstorHead *list,int target_location){
    int i;
    tNumStorage* temp;
    temp = list->head;
    if(list->counts == 1){
        list->tail = NULL;
        list->head = NULL;
        //free(temp);
    }
    else if(list->counts == target_location){
        temp = list->tail;
        list->tail = list->tail->pre_node;
        list->tail->next = NULL;
       // free(temp);
    }
    else{
        for(i=0;i <= list->counts-1;i++){
            if(i+1 == target_location && i == 0){
                temp->next->pre_node = NULL;
                list->head = temp->next;
                break;
            }
            else if(i+1 == target_location){
                temp->pre_node->next = temp->next;
                temp->next->pre_node = temp->pre_node;
                break;
            }
            temp = temp->next;
        }
       // free(temp);
    }
    free(temp);
    list->counts --;
    printf("\n\n  counts: %d\n",list->counts);
    print_list(list);
}