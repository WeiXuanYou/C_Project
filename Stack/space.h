#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#define N 7

typedef struct Score
{
    int score;
    int loc;
    int used; // to record if the space is used
}tTypeScore;

void getScoreSpace(tTypeScore** pp_score); //get the space from scoreBuf, return the allocated number
void returnScoreSpace(int location);      //return the space of the used scroreBuf