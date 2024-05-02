#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void print_and_init_arr(int number,int array_size,int* array){
    int i;
    printf("\n\n");
    for (i = 0; i < array_size; i++) {
        if (i % number == 0 && i != 0) 
            printf("\n");
        printf("%4d", *(array + i));
    }
    printf("\n");
}
void swap(int* array,int index1,int index2){
    *(array + index1) = *(array + index1) ^ *(array + index2);
    *(array + index2) = *(array + index1) ^ *(array + index2);
    *(array + index1) = *(array + index2) ^ *(array + index1);
}
int main(int argc, char* argv[]) {
    int i;
    int* array;
    int number = sqrt((double)(argc - 2));
    array = (int*)malloc(sizeof(int) * (argc - 2));
    for (i = 0; i < argc - 2; i++) 
       *(array + i) = atoi(*(argv + i + 2)); 
    print_and_init_arr(number,argc - 2,array);
    for (i = 0; i < number*2; i++) {
        (i<number) ? swap(array,i,number*2 + i) :  swap(array,(i-number) * number,2 + (i-number) * number);
        ((i+1) % number == 0 && (i+1) !=1) ? print_and_init_arr(number,argc - 2,array): NULL;
    }
}