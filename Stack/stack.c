#include "stack.h"

tStack *createStack(void){
    tStack* stack;
    stack  = (tStack*) malloc(sizeof(tStack));
    stack->count = 0;
    stack->head = NULL;
    return stack;
}
void handle_push_operation(tStack *stack_ptr){

    if(stack_ptr->count >= N)
        printf("[Error] handle_PushOperation() : space full \n");
    else{
       tNode* new_node = (tNode*) malloc(sizeof(tNode));
       new_node->next = stack_ptr->head;
       int temp;
       printf("  handlePushOperation(): enter score value: ");
       scanf("%d",&temp);
       getScoreSpace(&new_node->dataPtr);
       new_node->dataPtr->score = temp;
       new_node->dataPtr->loc = stack_ptr->count;
       stack_ptr->head = new_node;
       stack_ptr->count++;
    }

}
void handle_pop_operation(tStack *stack_ptr){
    if(stack_ptr->count <= 0)
        printf("[Error] handlePopOperation() : nothing in stack  \n");
    else{
        tNode* buf;
        buf = stack_ptr->head;
        printf("  handlePopOperation() : poped score value : %d\n",buf->dataPtr->score);
        stack_ptr->head = stack_ptr->head->next;
        stack_ptr->count--;
        returnScoreSpace(buf->dataPtr->loc);
        free(buf);
    }

}
void print_stack_content(tStack *stack_ptr){
    tNode* now_node = stack_ptr->head;
    printf("\n  printStackContent(): stack items -> ");

    for(int i=1;i<=stack_ptr->count;i++){
        printf("%d(%d) ",now_node->dataPtr->score,stack_ptr->count-i);
        now_node = now_node->next;
    }
    printf("\n\n");
}
