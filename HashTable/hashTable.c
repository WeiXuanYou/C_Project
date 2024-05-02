#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CAPACITY 50000 // Size of the HashTable.
unsigned long hash_function(char* str){
    unsigned long i = 0;
    for(int j = 0; str[j];j++){
        i += str[j];
    }
    return i % CAPACITY;
}
typedef struct Ht_item{
    char* key;
    char* val;
}Ht_item;

//Definethe Linked List
typedef struct LinkedList{
    Ht_item* item;
    struct LinkedList* next;
}LinkedList;

//Define the HashTable
typedef struct HashTable{
    //Contains an array of pointer to itmes.
    Ht_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
}HashTable;


//Define functions
LinkedList* allocate_list();
LinkedList* linkedlist_insert(LinkedList*,Ht_item*);
Ht_item* linkedlist_remove(LinkedList*);
LinkedList** create_overflow_buckets(HashTable*);
void free_overflow_buckets(HashTable*);
Ht_item* create_item(char*, char*);
HashTable* create_table(int);
void free_item(Ht_item*);
void free_table(HashTable*);
void print_table(HashTable*);
void handle_collision(HashTable*,unsigned long,Ht_item*);
void ht_insert(HashTable*,char*,char*);
char* ht_search(HashTable*,char*);
void print_search(HashTable*,char*);
void ht_delete(HashTable*,char*);


LinkedList* allocate_list(){
    //Allocate memory for a LinkedList pointer.
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}
LinkedList* linkedlist_insert(LinkedList* list,Ht_item* item){
    LinkedList* new_node = allocate_list();
    new_node->item = item;
    new_node->next = NULL;

    //Insert the item onto the LinkedList.
    if(list == NULL){
        list = new_node;
        return list;
    }

    LinkedList* temp = list;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = new_node;
    return list;
}
Ht_item* linkedlist_remove(LinkedList* list){
    if(!list || !list->next) return NULL;

    LinkedList* temp = list;
    temp->next = NULL;
    list = list->next;
    Ht_item* item;

    memcpy(temp->item,item,sizeof(Ht_item));
    free_item(temp->item);
    free(temp);
    return item;
}
void free_linked_list(LinkedList* list){
    LinkedList* temp;
    while(list != NULL){
        temp = list;
        list = list->next;
        free_item(temp->item);
        free(temp);
    }
}


LinkedList** create_overflow_buckets(HashTable* table){
    //Create the overflow buckets; an array of LinkedLists.
    LinkedList** buckets = (LinkedList**) calloc(table->size,sizeof(LinkedList*));
    
    for(int i = 0;i < table->size;i++){
        buckets[i] = NULL;
    }

    return buckets;
}
void free_overflow_buckets(HashTable* table){
    
    for(int i = 0;i < table->size;i++){
        free_linked_list(table->overflow_buckets[i]);
    }
    free(table->overflow_buckets);
}

Ht_item* create_item(char* key, char* val){
    //Create a pointer to a new HashTable item.
    Ht_item* item = (Ht_item*) malloc(sizeof(Ht_item));
    item->key = (char*) malloc(strlen(key) + 1);
    item->val = (char*) malloc(strlen(val) + 1);
    strcpy(item->key,key);
    strcpy(item->val,val);
    return item;
}
HashTable* create_table(int size){
    //Create a new HashTable.
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc(size,sizeof(Ht_item*));

    for(int i = 0;i<size;i++){
        table->items[i] = NULL;
    }
    table->overflow_buckets = create_overflow_buckets(table);
    
    return table;
}

void free_item(Ht_item* item){
    //Free an item
    free(item->key);
    free(item->val);
    free(item);
}

void free_table(HashTable* table){
    //Free the table
    for(int i = 0;i < table->size; i++){
        Ht_item* item = table->items[i];
        if(item != NULL){
            free_item(item);
        }
    }
    free(table->items);
    //Free the overflow bucket lists and its items.
    free_overflow_buckets(table);
    free(table);
}

void print_table(HashTable* table){
    printf("\nHash Table \n----------\n");
    for(int i = 0;i < table->size ; i++){
        if(table->items[i]){
            printf("Index : %d, Key %s, Value : %s\n",i,table->items[i]->key,table->items[i]->val);
        }
    }
    printf("----------\n\n");
}
void handle_collision(HashTable* table,unsigned long index,Ht_item* item){
    LinkedList* head = table->overflow_buckets[index];
    
    table->overflow_buckets[index] = linkedlist_insert(head,item);


}
void ht_insert(HashTable* table,char* key,char* val){
    //Create the item.
    Ht_item* item = create_item(key,val);

    //Compute the index
    int index = hash_function(key);

    Ht_item* current_item = table->items[index];
    if(current_item == NULL){
        //Key does not exist.
        if(table->count == table->size){
            //HashTable is full.
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }
         //Insert directly.
        table->items[index] = item;
        table->count++;
    }
    else{
        //Scenairo 1: Update the value.
        if(strcmp(current_item->key,key) == 0){
            strcpy(table->items[index]->val,val);
        }
        else{
            //Scenairo 2: Handle the collision.
            handle_collision(table,index,item);
        }
        return;
    }
}

char* ht_search(HashTable* table,char* key){
    //Search for the key in the HashTalbe.
    //Return NULL if it doens't exist.
    int index = hash_function(key);
    Ht_item *item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];
    
    //Provide only non-NULL values.
    while(item != NULL){
        
        if(strcmp(item->key,key) == 0){
            return item->val;
        }
        if(head == NULL) return NULL;
        item = head->item;
        head = head->next;
    }

    return NULL;
}
void ht_delete(HashTable* table,char* key){
    //Delete an item from the table.
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    if(item == NULL){
        //Doesn't exist.
        return;
    }
    else{
        if(head == NULL && strcmp(item->key,key) == 0){
            //Collision chain doesn't exist.
            //Remove the item.
            //Set table index to NULL
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if(head != NULL){
            //Collision chain exisits.
            if(strcmp(item->key,key) == 0){
                free_item(item);
                LinkedList* temp = head;
                head = head->next;
                temp->next = NULL;
                table->items[index] = create_item(temp->item->key,temp->item->val);
                free_linked_list(temp);
                table->overflow_buckets[index] = head;
                return;                
            }
            LinkedList* curr = head;
            LinkedList* prev = NULL;

            while(curr != NULL){
                if(strcmp(curr->item->key,key) == 0){
                    if(prev == NULL){
                        //First element of the chain.
                        //Remove the chain.
                        LinkedList* temp = head;
                        head = head->next;
                        temp->next = NULL;
                        free_linked_list(temp);
                        table->overflow_buckets[index] = head;
                    }
                    else{
                        // This is somewhere in the chain.
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linked_list(curr);
                    }
                    return;
                }
                prev = curr;
                curr = curr->next;
            }

        }
    }
}

void print_search(HashTable* table,char* key){
    char* val;
    if((val = ht_search(table,key)) == NULL){
        printf("Key: %s, doesn't exist\n",key);
    }
    else{
        printf("Key: %s, Value: %s \n",key,val);
    }
}

int main(){
    HashTable *ht = create_table(CAPACITY);
    ht_insert(ht, (char *)"1", (char *)"First address");
    ht_insert(ht, (char *)"2", (char *)"Second address");
    ht_insert(ht, (char *)"Hel", (char *)"Third address");
    ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
    print_search(ht, (char *)"1");
    print_search(ht, (char *)"2");
    print_search(ht, (char *)"3");
    print_search(ht, (char *)"Hel");
    print_search(ht, (char *)"Cau"); // Collision!
    print_table(ht);
    ht_delete(ht, (char *)"1");
    ht_delete(ht, (char *)"2");
    ht_delete(ht, (char *)"Hel");
    ht_delete(ht, (char *)"Cau");
    print_table(ht);
    ht_insert(ht, (char *)"1", (char *)"First address");
    ht_insert(ht, (char *)"2", (char *)"Second address");
    ht_insert(ht, (char *)"5", (char *)"Third address");
    ht_insert(ht, (char *)"6", (char *)"Fourth address");
    print_table(ht);
    free_table(ht);

}