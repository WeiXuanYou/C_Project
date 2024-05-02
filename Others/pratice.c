#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 5
typedef char my_int[MAX];
void my_number_print(my_int* input);
void my_add(my_int* result,char* input1,char* input2);
void trans_from_string(my_int* input,char* my_input);

void my_add(my_int* result,char* input1,char* input2){
    my_int input1_aft; 
    my_int input2_aft; 
    trans_from_string(&input1_aft,input1);
    trans_from_string(&input2_aft,input2);
    int zero_nums_1 = 0;
    int zero_nums_2 = 0;
    for(int i =0;i<MAX;i++){
       zero_nums_1 = (!(*(input1_aft + i) - '0' >= 0 && *(input1_aft + i) - '0' <= 9))  ? zero_nums_1 + 1 : zero_nums_1;
       zero_nums_2 = (!(*(input2_aft + i) - '0' >= 0 && *(input2_aft + i) - '0' <= 9))  ? zero_nums_2 + 1 : zero_nums_2;
    }
    printf("%d",zero_nums_1);
    for(int i = 0;i<MAX;i++){
        *(*result + i) = '0';
    }
    for(int i = MAX-1;i>=0;i--){
        if(((*(input1_aft+i) + *(input2_aft+i) + *(*result + i) - '0'*3 ))  > 9 && i!=0){
            *(*result + i) = (((*(input1_aft+i) + *(input2_aft+i) + *(*result + i) - '0'*3))% 10) + '0' ;
            *(*result + i - 1 ) =*(*result + i - 1 ) + 1;
        }
        else{
            *(*result + i) = ((*(input1_aft+i) + *(input2_aft+i) + *(*result + i) - '0'*3 )) + '0'; 
        }
    }
}
void my_number_print(my_int* input){
    if(*(*input) - '0' > 9){
        printf("Overflow! \n\n");
        return;
    }
    printf("The add result : ");
    for(int i=0;i<MAX;i++){
        printf("%c",*(*input + i));
    }
    printf("\n\n");
}
void trans_from_string(my_int* input,char* my_input){
    int zero_nums = 0;
    for(int i =0;i<MAX;i++){
       zero_nums = (!(*(my_input + i) - '0' >= 0 && *(my_input + i) - '0' <= 9))  ? zero_nums+1 : zero_nums;
    }
    for(int i = 0; i < MAX;i++){
       *(*input + i) = (i >= zero_nums) ? *(my_input + i - zero_nums) : '0';
    }
}
int main(){
    char user_input[MAX + 1];
    char user_input_1[MAX + 1];
    my_int result = {0};
    while(1){
        printf("Please give a number less than %d : ",MAX);
        scanf("%s",user_input);
        printf("Please give another number less than %d : ",MAX);
        scanf("%s",user_input_1);
        user_input[MAX] = '\0';
        user_input_1[MAX] = '\0';
        my_add(&result,user_input,user_input_1);
        my_number_print(&result);
    }    
    return 0;
}