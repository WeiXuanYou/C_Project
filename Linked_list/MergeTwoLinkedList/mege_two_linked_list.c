#include<stdio.h>
#include<stdlib.h>
typedef struct num_list{
    int count;
    int *p_list;
}tNumList;
//function define
void bubble_sort(tNumList* list);
void merge(tNumList* list1,tNumList* list2);

void merge(tNumList* list1,tNumList* list2){
    int i;
    tNumList* list3;
    list3 = (tNumList *) malloc (sizeof(tNumList));
    list3->count = list1->count + list2->count;
    list3->p_list = (int *) malloc (sizeof(tNumList)*list3->count);
    printf("merged list : ");
   for(i = 0;i<list3->count;i++)
        list3->p_list[i] = (i < (list1->count)) ? list1->p_list[i]:list2->p_list[i-(list1->count)];
    
    bubble_sort(list3);

    for(i = 0;i<list3->count;i++)
        printf("%d ", list3->p_list[i]);
    printf("\n");
}

void bubble_sort(tNumList* list){
    int i,j;
    for(i = 0;i <list->count;i++){
        for(j = i+1 ;j<list->count;j++){
            if(list->p_list[i] > list->p_list[j]){
                list->p_list[i]  = list->p_list[i] ^ list->p_list[j];
                list->p_list[j]  = list->p_list[i] ^ list->p_list[j];
                list->p_list[i]  = list->p_list[i] ^ list->p_list[j];
            }
        }
    }
}   

int main(){
    //initialzation
    int i,j;
    tNumList** total_list;
    total_list = (tNumList **) malloc (sizeof(tNumList*)*2);
    for(i=0;i<2;i++){
        total_list[i] = (tNumList*) malloc (sizeof(tNumList));
        printf("Please enter how many numbers in list %d : ",i+1);
        scanf("%d",&total_list[i]->count);
        total_list[i]->p_list = (int *) malloc(sizeof(int)*total_list[i]->count);
        printf("Please input %d numbers : ",total_list[i]->count);
        for(j = 0;j<total_list[i]->count;j++)
            scanf("%d",&total_list[i]->p_list[j]);
        bubble_sort(total_list[i]);
    }
    for(i=0;i<2;i++){
        printf("sorted list %d : ",i+1);
        for(j=0;j<total_list[i]->count;j++)
            printf(" %d",total_list[i]->p_list[j]);
        printf("\n");
    }
    merge(total_list[0],total_list[1]);
}