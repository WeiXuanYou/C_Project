#include"stack.h"
int main(){
    
    tStack* pStack = createStack();
    int choose;
    
    while(1){
        //menu
        printf("(1) push or (2) pop a item to/from stack : ");
        scanf("%d",&choose);
        
        if(choose == 1)
        {
            handle_push_operation(pStack);
        }
        else if(choose == 2)
        {
            handle_pop_operation(pStack);
        }
        print_stack_content(pStack);
    }
    
}