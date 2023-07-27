#include "safearray.h"
using namespace saferarray;
#ifndef random_hpp
#define random_hpp

float random();
float random(float max);
bool randombool();
bool randombool(float truechange);
int randomint(float max);
template<typename T>
T multidist(safearray<float> probdist,safearray<T> returnval);


void init();

#endif // !random_hpp

