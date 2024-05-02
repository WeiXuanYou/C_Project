#include "main.h"
#include "queue.h"
#include "space.h"


int main (void)
{
    tQueue *queue;
    int operation;
    tQueueSmall *target_type_small;
    tQueueLarge *target_type_large;
    int id, score=0, ret;
    queue = createQueue();

    while (1)
    {

        printf("\nWhich type you are going to operate? \n");
        printf("1. Add a type 1 item\n");
        printf("2. Add a type 2 item\n");
        printf("3. remove a type 1 item with a specific Id\n");
        printf("4. remove a type 2 item with a specific Id\n");
        
        scanf("%d", &operation);
        
        if (operation == 1)
        {
            printf("  enter id:");
            scanf("%d", &id);

            ret = enqueue_type_small(queue, id, score);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue\n");
            }
            print_buffer_status();
        }
        else if (operation == 2)
        {
            printf("  enter id: ");
            scanf("%d", &id);

            ret = enqueue_type_large(queue, id, score);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue \n");
            }
            print_buffer_status();

        }
        else if (operation == 3)
        {
            printf ("  enter an ID to remove \n");
            scanf("%d", &id);
            target_type_small = NULL;
            target_type_small = find_target_small_node(queue, id);
            if (target_type_small == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                dequeue_type_small(queue, target_type_small);
            }
            print_buffer_status();

        }
        else if (operation == 4)
        {
            printf ("enter an ID to remove \n");
            scanf("%d", &id);
            target_type_large = NULL;
            target_type_large = find_target_large_node (queue, id);
            if (target_type_large == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                dequeue_type_large(queue, target_type_large);
            } 
            print_buffer_status();
        }
        else 
        {
            printf ("    no such operation \n");   
        }
        print_queue(queue);
    }

}
