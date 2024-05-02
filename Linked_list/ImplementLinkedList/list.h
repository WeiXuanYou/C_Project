#ifndef _GLOBE_H
#define _GLOBE_H
#define  _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#endif // _GLOBE_H
typedef struct num_storage{
    int number;
    struct num_storage* next;
    struct num_storage* pre_node;
}tNumStorage;

typedef struct num_stor_head{
        int counts;
        struct num_storage* head;
        struct num_storage* tail;
}tNumstorHead;
void get_input(tNumstorHead* list);
void initial_list(tNumstorHead* list);
void print_list(tNumstorHead* list);
void delete(tNumstorHead *list,int target_location);
void add_node(tNumstorHead *list,int add_num,int target_location,int before_or_after);
