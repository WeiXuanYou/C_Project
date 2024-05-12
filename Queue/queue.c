#include <stdio.h>
#include <stdlib.h>
#define N 10 // The size of memory maximum.

typedef struct node{
    int val;
    struct node* next;
}Node;

typedef struct Head{
    Node* head;
    Node* rear;
    int count;
}tHead;

void print_all(tHead*);
void init_head(tHead*);
void enqueue(tHead*,int);
int dequeue(tHead*,int*);
int isFull(tHead*);
int isEmpty(tHead*);
void print_curr_queue_stats(tHead*);

void init_head(tHead* head){
    head->count = 0;
    head->head = NULL;
    head->rear = NULL;
}

void enqueue(tHead* head,int val){
    if(isFull(head)){
        printf("\nFail, memory is full!\n");
        return;
    }

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;

    if(head->head == NULL)
        head->head = new_node;
    else
        head->rear->next = new_node;

    head->rear = new_node;
    head->count++;
    print_curr_queue_stats(head);
}

int dequeue(tHead* head,int* val){
    if(head->count == 0){
        printf("\nFail, memory is empty!");
        return 0;
    }
    
    *val = head->head->val;
    Node* temp = head->head;
    head->head = head->head->next;
    free(temp);
    head->count--;
    
    print_curr_queue_stats(head);
    return 1;
}

void print_all(tHead* head){
    Node* temp = head->head;
    while(temp != NULL){
        printf(" %d",temp->val);
        temp = temp->next;
    }
    printf("\n");
}

int isFull(tHead* head){
    if(head->count == N) return 1;
    return 0;   
}

int isEmpty(tHead* head){
    if(head->count == 0 ) return 1;
    return 0;
}

void print_curr_queue_stats(tHead* head){
    printf("The current queue :");
    print_all(head);
    printf("The current number of queue data : %d\n\n\n",head->count);
}

int main() {
    tHead* head = (tHead*) malloc(sizeof(tHead));
    init_head(head);

    for(int i = 0; i < N+1 ; i++)
        enqueue(head,i);

    int val;
    for(int i = 0; i < N+1 ; i++)
        dequeue(head,&val); 
    printf("\n");
    
    print_all(head);
    return 0;
}
