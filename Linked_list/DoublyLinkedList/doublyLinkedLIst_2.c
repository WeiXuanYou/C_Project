#include<stdio.h>
#include<stdlib.h>

typedef struct num_storage{
    int number;
    struct num_storage *next;
    struct num_storage *pre_node;
}tNumStorage;

typedef struct num_stor_head{
    int count;
    tNumStorage *head; //malloc
    tNumStorage *tail;
}tNumStorHead;

void initial_list(tNumStorHead *list);
void print_list(tNumStorHead *list);
void get_input(tNumStorHead *list);
void sort_list(tNumStorHead *list ,int intput);
void delete(tNumStorHead *list,int target_location);
void add_node(tNumStorHead *list ,int add_num ,int target_location ,int before_or_after);

int main (void){
    int i ;
    tNumStorHead *list;
    list = (tNumStorHead *) malloc (sizeof(tNumStorHead));
    initial_list(list);
    get_input(list);
}

void initial_list(tNumStorHead *list){
    list -> count = 0;
    list -> head = NULL;
    list -> tail = NULL;
}

void print_list(tNumStorHead *list){
    tNumStorage *p_store = list -> head;

    printf("From head --> ");
    while(p_store != NULL){ 
        printf("%d ",p_store-> number);
        p_store = p_store -> next;
    }
    printf("\n");

    p_store = list->tail;
    printf("From tail --> ");
    while(p_store != NULL){ 
        printf("%d ",p_store-> number);
        p_store = p_store -> pre_node;
    }
    printf("\n\n");
}

void get_input(tNumStorHead *list){
    int input_num = 0;
    int add_num = 0;
    int target_location = 0;
    int before_or_after;
    while(1){
        printf("1.Add a number or 2. Delete a number: ");
        scanf("%d", &input_num);
        if(input_num == -1){
            break;
        }
        else if (input_num == 1)
        {
            printf("Add a number: ");
            scanf("%d", &add_num);
            if(list->count == 0){
                add_node(list,add_num,target_location,before_or_after);
            }
            else{
                printf("Specify a target location: ");
                scanf("%d", &target_location);
                printf("1.Before or 2. After the location: ");
                scanf("%d", &before_or_after);
                if(target_location < 1 || target_location > list->count){
                    printf("invaild number !\n");
                }
                else if(before_or_after == 1 || before_or_after == 2){ 
                    add_node(list,add_num,target_location,before_or_after);
                }
                else{
                    printf("no such choose!\n");
                }
            }
        }
        else if (input_num == 2)
        {
        	printf("Specify a target location: ");
            scanf("%d", &target_location);
            delete(list,target_location);
        }
        else{
        	printf("no such choose!\n");
        }
        /*
        printf("list->count: %d\n",list->count);
        print_list(list);*/
    }
}

void add_node(tNumStorHead *list ,int add_num ,int target_location ,int before_or_after){
    tNumStorage *node;   //create new node 
    node = (tNumStorage*) malloc (sizeof(tNumStorage));
    tNumStorage *pre_target;
    pre_target = (tNumStorage*) malloc (sizeof(tNumStorage));
    tNumStorage *next_target;
    next_target = (tNumStorage*) malloc (sizeof(tNumStorage));

    node->number = add_num;
    
    if(list->count == 0){
    	list->head = node;
    	list->tail = node;
    	list->tail->next = NULL;
        list->tail->pre_node = NULL;
	}
    else if(target_location == 1 && before_or_after ==1){
        node->next = list->head;
        node->pre_node = NULL;
        list->head->pre_node = node;
        list->head = node;
    }
    else if(target_location == list->count && before_or_after ==2){
        node->next = NULL;
        node->pre_node = list->tail;
		list->tail->next = node;
        list->tail = node;
    }
    else{
    	pre_target = list->head;
		next_target = list->head->next;

    	if(before_or_after ==1){
    		for(int i=0; i<target_location-2; i++){
        		pre_target = pre_target->next;
        		next_target = pre_target->next;
        		//printf("\npre_target is:%d\n",pre_target->number);
    		}
		}
		else{
    		for(int i=0; i<target_location-1; i++){
        		pre_target = pre_target->next;
        		next_target = pre_target->next;
        		//printf("\npre_target is:%d\n",pre_target->number);
    		}			
		}
		
        node->next = next_target;
        node->pre_node = pre_target;
        next_target->pre_node = node;
        pre_target->next = node;
        
    }
    list->count ++;
    printf("list->count: %d\n",list->count);
    print_list(list);
}

void delete(tNumStorHead *list,int target_location){
	tNumStorage *pre_target;
    pre_target = (tNumStorage*) malloc (sizeof(tNumStorage));
    tNumStorage *next_target;
    next_target = (tNumStorage*) malloc (sizeof(tNumStorage));
    
    if(list->count == 0){
        printf("Nothing\n\n");
    }
    else if(list->count == 1){
        tNumStorage *temp_node;
        temp_node = list->tail;
        list->tail = NULL;
        list->head = NULL;
        free(temp_node);       
    }
    else if(target_location == 1){
    	tNumStorage *temp_node;
    	temp_node = list->head;
    	list->head = list->head->next;
    	list->head->pre_node = NULL;
    	free(temp_node);
	}
	else if(target_location == list->count){
    	tNumStorage *temp_node;
    	temp_node = list->tail;
    	list->tail = list->tail->pre_node;
    	list->tail->next = NULL;
    	free(temp_node);
	}
    else{
		pre_target = list->head;
		next_target = list->head->next;
		for(int i=0; i<target_location-2; i++){
        	pre_target = pre_target->next;
        	next_target = pre_target->next;
        	//printf("\npre_target is:%d\n",pre_target->number);
    	}
		pre_target->next = next_target->next;
		next_target->next->pre_node = pre_target;
		free(next_target);
	}
	if(list->count != 0){
		list->count --;
		printf("list->count: %d\n",list->count);
		print_list(list);
    }
}
