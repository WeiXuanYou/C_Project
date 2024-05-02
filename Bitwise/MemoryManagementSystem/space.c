#include "space.h"


unsigned char buffer[SMALL_ELEMENT_SIZE*NUM_SMALL_BYTE_BUF + NUM_LARGE_BYTE_BUF*LARGE_ELEMENT_SIZE];

unsigned char byte_large_buf_mask = 0;
unsigned char byte_small_buf_mask = 0;


void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
  
    printf ("      byte_small_buf_mask: ");
    for (i = 0; i< 8; i++)
    {
        printf ("%d ", (byte_small_buf_mask&mask) >> (7-i));
        mask = mask >> 1;
    }

    mask = 0x80;
    printf ("\n      byte_large_buf_mask: ");
    for (i = 0; i< 8; i++)
    {
        printf ("%d ", (byte_large_buf_mask&mask) >> (7-i));
        mask = mask >> 1;
    }    
    printf ("\n");
}

void  our_malloc(int type, void **target, int *mem_location)
{
    int avaliable_loc = 0;
    if(type == TYPE_SMALL){
        avaliable_loc = test_single_location(byte_small_buf_mask,NUM_SMALL_BYTE_BUF);
        if(avaliable_loc >= 0){
            set_single_bit(&byte_small_buf_mask,avaliable_loc);
            *target = &buffer[SMALL_ELEMENT_SIZE*avaliable_loc];
            *mem_location = avaliable_loc;
        }
        else{
            avaliable_loc = test_single_location(byte_large_buf_mask,NUM_LARGE_BYTE_BUF);
            if(avaliable_loc >=0){
                set_single_bit(&byte_large_buf_mask,avaliable_loc);
                *target = &buffer[NUM_SMALL_BYTE_BUF*SMALL_ELEMENT_SIZE + LARGE_ELEMENT_SIZE*avaliable_loc];
                *mem_location = avaliable_loc + 8;
            }
        }
    }
    else if(type == TYPE_LARGE){
        avaliable_loc = test_single_location(byte_large_buf_mask,NUM_LARGE_BYTE_BUF);
        if(avaliable_loc >= 0){
            set_single_bit(&byte_large_buf_mask,avaliable_loc);
            *target = &buffer[NUM_SMALL_BYTE_BUF*SMALL_ELEMENT_SIZE + LARGE_ELEMENT_SIZE*avaliable_loc];
            *mem_location = avaliable_loc;
        }
        else{
            avaliable_loc = test_dual_location(byte_small_buf_mask,NUM_SMALL_BYTE_BUF);
            if(avaliable_loc >= 0){
                set_dual_bit(&byte_small_buf_mask,avaliable_loc);
                *target = &buffer[SMALL_ELEMENT_SIZE*avaliable_loc];
                *mem_location = avaliable_loc + 8;
            }
        }
    }
}

int test_single_location(int mask, int mask_length)
{
    int i;
    for(i = 0;i<mask_length;i++){
        if((mask & 0x01) == 0x00){
            return i;
        }
        mask >>= 1;
    }
    return -1;
}

void set_single_bit(unsigned char *mask, int location)
{
    unsigned char set = 0x01;
    set <<= (location);
    *mask |= set;
}


int test_dual_location(int mask, int mask_length)
{
    int i;
    for(i = 0;i<mask_length-1;i++){
        if((mask & 0x03) == 0x00){
            return i;
        }
        mask >>= 1;
    }
    return -1;
}

void set_dual_bit(unsigned char *mask, int location)
{
    unsigned char set = 0x03;
    set <<= location;
    *mask |= set;
}

void clear_single_bit(unsigned char *mask, int location)
{
    unsigned char set = 0x01;
    *mask =  ~(set << location)&*mask;
}

void clear_dual_bit(unsigned char *mask, int location)
{
    unsigned char set = 0x03;
    *mask = ~(set << location)&*mask;
}

void  our_free(int type, int mem_location)
{
    if(type == TYPE_SMALL){
        if(mem_location > 7){
            clear_single_bit(&byte_large_buf_mask,mem_location - 8);
        }
        else{
            clear_single_bit(&byte_small_buf_mask,mem_location);
        }

    }
    else if(type == TYPE_LARGE){
        if(mem_location > 7){
            clear_dual_bit(&byte_small_buf_mask,mem_location - 8);
        }
        else{
            clear_single_bit(&byte_large_buf_mask,mem_location);
        }
    }
}
