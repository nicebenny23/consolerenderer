#include "random.h"
#include <random>

uint64_t val = 0;
float   random()
{
   //xorshift 64


  
        val ^= val << 13;
        val ^= val >> 7;
        val ^= val << 17;

        return static_cast<double>(val) / UINT64_MAX;
    
}
bool randombool() {
    val ^= val << 13;
    val ^= val >> 7;
    val ^= val << 17;

    return val % 2;
}
float random(float max)
{

    val ^= val << 13;
    val ^= val >> 7;
    val ^= val << 17;

    return max*static_cast<double>(val) / UINT64_MAX;
}

void init()
{

	val = ((unsigned)(time)(0));
}


