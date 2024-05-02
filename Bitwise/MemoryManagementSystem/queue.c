#include "queue.h"
#include "space.h"


tQueue* createQueue(void){    
    tQueue *queue;
    queue=(tQueue *) malloc (sizeof(tQueue));

    if (queue)
    {
        queue->type_small_front=NULL;
        queue->type_small_rear=NULL;
        queue->type_large_front=NULL;
        queue->type_large_rear=NULL;        
        queue->type_small_count=0;
        queue->type_large_count=0;
    }

    return queue;
}

int enqueue_type_small(tQueue *queue, int id, int score)
{
    tQueueSmall *newptr = NULL;
    int mem_location;

    our_malloc (TYPE_SMALL, (void *)&newptr, &mem_location);
    
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }
    
    newptr->id = id;
    newptr->score = score;
    newptr->next=NULL;
    newptr->prev=NULL;
    newptr->location = mem_location;

    if (queue->type_small_count==0)
    {
        queue->type_small_front = newptr;
    }
    else
    {
        queue->type_small_rear->next = newptr;
    }
    
    newptr->prev = queue->type_small_rear;        
    queue->type_small_rear = newptr;    
    queue->type_small_count++;
    
    return 1;
}

int dequeue_type_small(tQueue *queue, tQueueSmall *target)
{
    
    if (queue->type_small_count == 1)
    {
        queue->type_small_rear = queue->type_small_front = NULL;
    }
    else if (target == queue->type_small_front)
    {
        queue->type_small_front = queue->type_small_front->next;
        queue->type_small_front->prev = NULL;

    }
    else if (target == queue->type_small_rear)
    {
        queue->type_small_rear = queue->type_small_rear->prev;
        queue->type_small_rear = NULL;
    }
    else
    {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    
    queue->type_small_count--;
    our_free(TYPE_SMALL, target->location);

    return 1;    
}

tQueueSmall *find_target_small_node(tQueue *queue, int id)
{
    int i;
    tQueueSmall *target = queue->type_small_front;
    
    for (i = 0; i < queue->type_small_count; i++)
    {
        if (target->id == id)
        {
            return target;
        }
        else
        {
            target = target->next;
        }
    }
    return NULL;
}

int enqueue_type_large(tQueue *queue, int id, int score)
{
    tQueueLarge *newptr = NULL;
    int mem_location;

    our_malloc (TYPE_LARGE, (void *)&newptr, &mem_location);
    
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }
    
    newptr->id = id;
    newptr->score[0] = score;
    newptr->next=NULL;
    newptr->prev=NULL;
    newptr->location = mem_location;

    if (queue->type_large_count==0)
    {
        queue->type_large_front = newptr;
    }
    else
    {
        queue->type_large_rear->next = newptr;
    }
    
    newptr->prev = queue->type_large_rear;        
    queue->type_large_rear = newptr;    
    queue->type_large_count++;
    
    return 1;
}

int dequeue_type_large(tQueue *queue, tQueueLarge *target)
{
    
    if (queue->type_large_count == 1)
    {
        queue->type_large_rear = queue->type_large_front = NULL;
    }
    else if (target == queue->type_large_front)
    {
        queue->type_large_front = queue->type_large_front->next;
        queue->type_large_front->prev = NULL;

    }
    else if (target == queue->type_large_rear)
    {
        queue->type_large_rear = queue->type_large_rear->prev;
        queue->type_large_rear->next = NULL;
    }
    else
    {
        target->prev->next = target->next;
        target->next->prev=target->prev;
    }
    
    queue->type_large_count--;
    our_free(TYPE_LARGE, target->location);

    return 1;    
}

tQueueLarge *find_target_large_node(tQueue *queue, int id)
{
    int i;
    tQueueLarge *target = queue->type_large_front;
    
    for (i = 0; i < queue->type_large_count; i++)
    {
        if (target->id == id)
        {
            return target;
        }
        else
        {
            target = target->next;
        }
    }
    return NULL;
}



void print_queue (tQueue *queue)
{
    int i;
    tQueueSmall *target = queue->type_small_front;

    printf("      type small queue: ");    
    for (i = 0; i < queue->type_small_count; i++)
    {
        printf ("%d ", target->id);
        target = target->next;
    }
    printf("\n");

    tQueueLarge *target_large = queue->type_large_front;

    printf("      type large queue: ");    
    for (i = 0; i < queue->type_large_count; i++)
    {
        printf ("%d ", target_large->id);
        target_large = target_large->next;
    }
    printf("\n");
}