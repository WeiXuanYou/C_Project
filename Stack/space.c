#include"space.h"
tTypeScore scoreBuf[N];
int buf_count = 0;

void getScoreSpace(tTypeScore **pp_score)
{
    int free = 0;
    /*for(free = 0;free < N;free++){
        if(scoreBuf[free].used = 0)
            break;
    }*/
    *pp_score = &scoreBuf[buf_count];
    printf("  getScoreSpace() : giving space numbered %d\n",buf_count);
    buf_count ++;
}

void returnScoreSpace(int location)
{
    buf_count --;  //score_buf[location].used = 0;
    printf("  returnScoreSpace() : return space numbered %d\n",location);
} 