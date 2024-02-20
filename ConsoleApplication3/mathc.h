#include <cmath>
#ifndef mathc_HPP
#define mathc_HPP

int mod(int val, int rem) {


	if (val<0)
	{
		return rem - abs(val) % rem;

	}
	return val % rem;
}

template <typename T>
T clamp(T val, int low, int high)
{
	if (val > high)
	{
		return high;
	}
	if (val < low)
	{
		return low;
	}
	return val;
}

template <typename T>
T lerp(T start, T end, float value) {

	return start * value + (1 - value) * end;

}



#endif // !mathc_HPP
