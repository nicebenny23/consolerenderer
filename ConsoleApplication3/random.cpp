#include "random.h"


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
template <typename T>
T multidist(safearray<float> probdist, safearray<T> returnval)
{

    float total = 0;

    for (int i = 0; i <probdist.length; i++)
    {
        total += probdist[i];
    }
        float rand = float(random()) * total - probdist[0];


        short g = 0;

        while (rand > 0)
        {
            rand -= probdist[++g];
        }

        return(returnval[ g]);


  
}
bool randombool(float truechance) {


    if (random(100)<=truechance)
    {
        return true;
    }
    return false;
}
int randomint(float max)
{

    return round(random(max)-.5);
}
void  randominit()
{
    
	val = 2;
    
}


