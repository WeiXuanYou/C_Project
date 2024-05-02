#ifndef __QUEUE__
#define __QUEUE__

typedef struct type_small {
    int id;
    int score;
    int location;
    struct type_small *next;
    struct type_small *prev;
}tQueueSmall; 

typedef struct type_large {
    int id;
    int score[8];
    int location;
    struct type_large *next;
    struct type_large *prev;
}tQueueLarge; 

typedef struct {
    tQueueSmall *type_small_front;
    tQueueSmall *type_small_rear;
    tQueueLarge *type_large_front;
    tQueueLarge *type_large_rear;
    int type_small_count;
    int type_large_count;
}tQueue;


tQueue* createQueue(void);

int enqueue_type_small(tQueue *queue, int id, int score);
int dequeue_type_small(tQueue *queue, tQueueSmall *target);
tQueueSmall *find_target_small_node(tQueue *queue, int id);

int enqueue_type_large(tQueue *queue, int id, int score);    
int dequeue_type_large(tQueue *queue, tQueueLarge *target);
tQueueLarge *find_target_large_node(tQueue *queue, int id);

void print_queue(tQueue *queue);

#endif