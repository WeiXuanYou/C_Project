#include"function.h"
#define bit_max 31

int CheckRangeLow(Int32 input,Int32 high,Int32 low){
    input >>= low;
    for(int i=0;i<(high-low);i++){
        if(input & 0x00000001)
            return 1;
        input >>= 1;
    }
    return 0;
}


int CheckRangeNoLow(Int32 input,Int32 high,Int32 low){
    input <<= (bit_max-high);
    input >>= (bit_max-high+low);
    if(input != 0x00000000)
        return 1;
    return 0;
}