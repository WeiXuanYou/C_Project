#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<sys/time.h>
#define MAX 50
#define MIN 5
#define MATRIX1_ROW 1024*2
#define MATRIX1_COL 1024*2
#define MATRIX2_ROW 1024*2
#define MATRIX2_COL 1024*2
#define THREAD_NUMS 1024

void allocate_space_matrix(int** array,int row,int col);
void initialize_matrix(int** array,int row,int col);
void assign_val_matrix(int** array,int row,int col);
void print_matrix(int** array,int row,int col);
void matmul(int** array1,int row1,int col1,
            int** array2,int row2,int col2,int** output);
void matmul_opt(int** array1,int row1,int col1,
            int** array2,int row2,int col2,int** output);
void cal_exec_time(void (*fun_ptr)(
            int** array1,int row1,int col1,
            int** array2,int row2,int col2,int** output),
            int** array1,int** array2,int** output,int mode);


void allocate_space_matrix(int** array,int row,int col){
    for(int i = 0;i < row;i++){
        array[i] =  (int*) malloc(sizeof(int)*col);
    }
}

void initialize_matrix(int** array,int row,int col){
     for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            *(*(array+i)+j) = 0; 
        }
    }
}

void assign_val_matrix(int** array,int row,int col){
    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            *(*(array+i)+j) = MIN + rand() % (MAX-MIN) + 1; 
        }
    }
}

void print_matrix(int** array,int row,int col){
    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("  %6d",*(*(array+i)+j));
        }
        printf("\n");
    }
}

void matmul(int** array1,int row1,int col1,
            int** array2,int row2,int col2,int** output){

    int i,j,k;
    for(i = 0;i < row1;i++){
        for(j = 0;j < col2;j++){
            for(k = 0;k < col1;k++){
                output[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }
}

void matmul_opt(int** array1,int row1,int col1,
            int** array2,int row2,int col2,int** output){

    int i,j,k;
    omp_set_num_threads(THREAD_NUMS);
    #pragma omp parallel for private(i,j,k) shared(array1,array2,output)
    for(i = 0;i < row1;i++){
        for(j = 0;j < col2;j++){
            for(k = 0;k < col1;k++){
                output[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }
}

void cal_exec_time(void (*fun_ptr)(
            int** array1,int row1,int col1,
            int** array2,int row2,int col2,int** output),
            int** array1,int** array2,int** output,int mode){
    
    //clock_t start, end; 
    // start = clock();
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    (*fun_ptr)(array1,MATRIX1_ROW,MATRIX1_COL,
               array2,MATRIX2_ROW,MATRIX2_COL,
               output);
    // end = clock();
    // double time_spent = ((double)(end - start) / CLOCKS_PER_SEC) / (mode==0 ? 1:THREAD_NUMS);

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("total execution time : %fs\n\n", elapsed );//time_spent);
}

int main(){
    int** array1 = (int**) malloc(sizeof(int*)*MATRIX1_ROW);
    int** array2 = (int**) malloc(sizeof(int*)*MATRIX2_ROW);

    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));
     
    //Build array1 and array2
    //printf("\n\nMatrix 1 , rows = %d , column = %d : \n",MATRIX1_ROW,MATRIX1_COL);
    allocate_space_matrix(array1,MATRIX1_ROW,MATRIX1_COL);
    assign_val_matrix(array1,MATRIX1_ROW,MATRIX1_COL);
    //print_matrix(array1,MATRIX1_ROW,MATRIX1_COL);

    //printf("\n\nMatrix 2 , rows = %d , column = %d : \n",MATRIX2_ROW,MATRIX2_COL);
    allocate_space_matrix(array2,MATRIX2_ROW,MATRIX2_COL);
    assign_val_matrix(array2,MATRIX2_ROW,MATRIX2_COL);
    //print_matrix(array2,MATRIX2_ROW,MATRIX2_COL);

    //Matrix 1 by matrix 2
    int** output = (int**) malloc(sizeof(int*)*MATRIX1_ROW);
    //printf("\n\nMatrix 1 X Matrix 2  , rows = %d , column = %d : \n",MATRIX1_ROW,MATRIX2_COL);
    allocate_space_matrix(output,MATRIX1_ROW,MATRIX2_COL);
    initialize_matrix(output,MATRIX1_ROW,MATRIX2_COL);
    /*matmul(array1,MATRIX1_ROW,MATRIX1_COL,
           array2,MATRIX2_ROW,MATRIX2_COL,
           output);*/
    printf("Original version\n\n");
    cal_exec_time(&matmul,array1,array2,output,0);
    printf("Accelerated version\n\n");
    cal_exec_time(&matmul_opt,array1,array2,output,1);
   // print_matrix(output,MATRIX1_ROW,MATRIX2_COL);
    printf("\n\n");

    //Release memory
    free(array1);
    free(array2);
    free(output);
    return 0;
}
