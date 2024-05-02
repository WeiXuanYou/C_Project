#include <stdio.h>
#include <stdlib.h>

#define Home 0
#define Cellular 1

typedef enum operator{
    CHT,
    FET,
    TWN,
}operator_eneum;

typedef struct node_info{
    int type;
    char name[10];
    char num[100];

    union{
        char home[100];
        operator_eneum celluar;
    }info_type;

    struct node_info *next;
    struct node_info *prev;
}phone_book;

typedef struct {
    phone_book *front;
    phone_book *rear;
    int count;
}tQueue;

tQueue* createQueue(void);
void sort_queue(tQueue *queue,phone_book *t_node);
void print_queue(tQueue *queue);

int main(void){
    tQueue *queue;
    queue = createQueue();

    int oper_name;


    while(1){
        phone_book *t_node;
        t_node = (phone_book *) malloc (sizeof(phone_book));

        printf("Please enter the name you want to add: ");
        scanf("%s",t_node->name);
        printf("choose (0) Home or (1) Cellular: ");
        scanf("%d",&(t_node->type));

        if(t_node->type == Home){
            printf("Please enter location code: ");
            scanf("%s",t_node->info_type.home);
            printf("Please enter number: ");
            scanf("%s",t_node->num);

            sort_queue(queue,t_node);
            print_queue(queue);

        }
        else if(t_node->type == Cellular){
            printf("choose operator name (0)CHT (1)FET (2)TWN: ");
            while(1){
                scanf("%d",&oper_name);
                if(oper_name<=2 && oper_name>=0){
                    t_node->info_type.celluar = oper_name;
                    break;
                }
                else{
                    printf("ERROR -- NO Such Option \n");
                }
            }
            printf("Please enter number: ");
            scanf("%s",t_node->num);
            sort_queue(queue,t_node);
            print_queue(queue);
        }
        else{
            printf("ERROR -- NO Such Option \n");
        }
    }


}

tQueue* createQueue(void){    
    tQueue *queue;
    queue=(tQueue *) malloc (sizeof(tQueue));

    if (queue)
    {
        queue->front=NULL;
        queue->rear=NULL;
        queue->count=0;
    }

    return queue;
}

int tqueue_enqueue(tQueue *queue, int id, int score, int type){

    phone_book *t_node;
    t_node = (phone_book *) malloc (sizeof(phone_book));


}

void sort_queue(tQueue *queue,phone_book *t_node){

    phone_book *test_node;

    t_node->next=NULL;
    t_node->prev=NULL;

    if (queue->count == 0)
    {
        queue->front = t_node;
        queue->rear = t_node;
    }
    else
    {
        /*
        t_node->prev = queue->rear;
        queue->rear->next = t_node;
        queue->rear = t_node;
        */
        
        test_node = queue->front;
        for(int i = 0; i<queue->count; i++){
            if((t_node->name)[0]<=(test_node->name)[0]){ 
                if(i == 0){
                    queue->front = t_node;
                    test_node->prev = t_node;
                    t_node->next = test_node;
                }
                else{
                    t_node->prev = test_node->prev;
                    test_node->prev->next = t_node;
                    test_node->prev = t_node;
                    t_node->next = test_node;
                }
                break;
            }
            else if(i == queue->count-1){
                queue->rear = t_node;
                t_node->prev = test_node;
                test_node->next = t_node;
                break;
            }
            else{
                test_node = test_node->next;
            }
        }
    }
    queue->count ++;

}

void print_queue(tQueue *queue){

    phone_book *target_node;
    target_node = queue->front;

    printf("      sorted name / number: \n"); 

    for (int i = 0; i < queue->count; i++)
    {
        if(target_node->type == Home){
            printf ("             %s(Home) / (%s) %s", target_node->name, target_node->info_type.home, target_node->num);
        } 
        else if(target_node->type == Cellular){
            printf ("             %s(Cellular) / (%d) %s",target_node->name,target_node->info_type.celluar, target_node->num);
        }
        printf("\n");
        target_node = target_node->next;
    }

    printf("\n");

}