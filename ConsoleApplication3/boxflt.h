
#include "vector2.h"
#ifndef floatbox_HPP
#define floatbox_HPP

class box
{
public:
	box();
	v2::Vector2 startpoint;
	v2::Vector2 endpoint;
	box(v2::Vector2 start, v2::Vector2 end);
	void change(v2::Vector2 start, v2::Vector2 end);
	void changemin(v2::Vector2 start);
	void changemax(v2::Vector2 end);
	float area();
private:

};


inline box::box() {


}

inline float box::area()
{
	return (endpoint.x-startpoint.x)* (endpoint.y - startpoint.y);
}
inline void resizeif(v2::Vector2 point, box &boundbox) {
	if (point.x < boundbox.startpoint.x)
	{
		boundbox.startpoint.x = point.x;
	}
	if (point.y < boundbox.startpoint.y)
	{
		boundbox.startpoint.y = point.y;
	}
	if (point.x > boundbox.startpoint.x)
	{
		boundbox.endpoint.x = point.x;
	}
	if (point.y > boundbox.startpoint.y)
	{
		boundbox.endpoint.y = point.y;
	}
}
inline bool pointinbox(v2::Vector2 point, box boundbox) {


	if (boundbox.startpoint.x<=point.x&&point.x <= boundbox.endpoint.x && boundbox.startpoint.y <= point.y<= boundbox.endpoint.y)
	{
		return true;
	}
	return false;
}
inline void box::change(v2::Vector2 start, v2::Vector2 end) {



		startpoint = v2::Vector2(min(start.x,end.x), min(start.y, end.y));
		endpoint = v2::Vector2(max(start.x, end.x), max(start.y, end.y));

}
inline void box::changemin(v2::Vector2 start) {



	startpoint = start;
	

}
inline void box::changemax(v2::Vector2 end) {



	endpoint = end;


}
inline box::box(v2::Vector2 start,v2::Vector2 end)
{
	startpoint = v2::Vector2(min(start.x, end.x), min(start.y, end.y));
	endpoint = v2::Vector2(max(start.x, end.x), max(start.y, end.y));
}



#endif