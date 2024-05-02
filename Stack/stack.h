#include "space.h"
typedef struct node{
    tTypeScore *dataPtr;
    struct node *next;
}tNode;

typedef struct nodeInfo{
    int count;
    tNode *head;
}tStack;

tStack* createStack(void); // Create a stack
void handle_push_operation(tStack *stack_ptr);//push a data_ptr to specific stack
void handle_pop_operation(tStack *stack_ptr);//pop a specific and return a void* data_ptr
void print_stack_content(tStack *stack_ptr);//print all content in stack
