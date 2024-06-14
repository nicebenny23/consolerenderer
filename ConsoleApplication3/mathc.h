#include <cmath>

#ifndef mathc_HPP
#define mathc_HPP
//mod that works for negitives

inline int mod(int val, int rem) {


	if (val<0)
	{
		return rem - abs(val) % rem;

	}
	return val % rem;
}

template <typename T>
inline T clamp(T val, int low, int high)
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
inline T lerp(T start, T end, float value) {

	return start * value + (1 - value) * end;

}
//determanes whether 2 intervals intersect 
//count minor intersections determines whether just touching counts as intersecting
inline bool intervalintersect(float astart, float aend, float bstart, float bend, bool countminorintersect=false){


	if (astart<aend)
	{
		float carry = aend;
		aend = astart;
		astart = carry;
		
	}
	if (bstart<bend)
	{
		float carry = bend;
		bend = bstart;
		bstart = carry;
	}
	if (astart>bstart)
	{
		if (aend > bstart || countminorintersect && (aend == bstart)) {
			return false;
		}
	}
	else
	{
		if (astart < bend || countminorintersect && (astart == bend)) {
			return false;
		}
	}

	return true;
	}

 inline bool valinrange(float r1, float r2, float val, bool countifminor) {


	if (val<max(r1,r2)&&min(r1,r2)<val)
	{
		return true;
	}

	if (countifminor)
	{
		if (val == r2||val==r1)
		{
			return true;
		}
	}
	

	return false;
}
#endif // !mathc_HPP
