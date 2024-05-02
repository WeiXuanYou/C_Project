#include"main.h"

int main(){
    tNumstorHead* list;
    list = (tNumstorHead*) malloc(sizeof(tNumstorHead));
    initial_list(list);
    get_input(list);
    //initial_all();
    return 0;
}

void get_input(tNumstorHead* list){
    int options;
    while(1){
        printf("1. Add a number or 2. Delete a number : ");
        scanf("%d",&options);
        if(options == -1){
            break;
        }
        else if(options == 1){
            process_add(list);
        }
        else if(options == 2){
            process_delete(list);
        }
        else
            printf("   No such choose ! \n");
    }
}
void process_delete(tNumstorHead* list){
    int target_location;
    printf("  Specify a target location : ");
    scanf("%d",&target_location);
    if(target_location > 0 && target_location <= list->counts){
        if(list->counts == 0){
            printf("  There is nothing to delete \n\n");
            return;
        }
        delete(list,target_location);
    }
    else{
        printf("     Exceed current list size %d or <= 0\n",list->counts);
    }
}
void process_add(tNumstorHead* list){
    int target_location;
    int bef_or_after = 0;
    int num;
    printf("  Add a number : ");
    scanf("%d",&num);
    if(list->counts == 0)
        add_node(list,num,0,bef_or_after); 
    else{
        printf("   Specify a target location : ");
        scanf("%d",&target_location);
        if(target_location < 1 || target_location > list->counts){
            printf("\n   Invaild number ! \n\n");
            return;
        }
        else{
            printf("   1. Before or 2. After the location %d : ",target_location);
            scanf("%d",&bef_or_after);
            if(bef_or_after == 1|| bef_or_after == 2)
                add_node(list,num,target_location,bef_or_after);
            else{
                printf("\n    No such choose ! \n\n");
                return;
            }
        }
    }
    list->counts ++;
    printf("\n\n  counts: %d\n",list->counts);
    print_list(list);
}