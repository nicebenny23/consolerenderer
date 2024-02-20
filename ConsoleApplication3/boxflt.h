#include "polygon.h"
#include "vector2.h"
using namespace pgon;
using namespace v2;
#ifndef floatbox_HPP
#define floatbox_HPP

class box
{
public:
	box(polygon poly,Vector2 loc);
	box();
	Vector2 startpoint;
	Vector2 endpoint;
	box(Vector2 start, Vector2 end);
	void change(Vector2 start, Vector2 end);
	void changemin(Vector2 start);
	void changemax(Vector2 end);
	float area();
	bool intersect(box bx);
private:

};
inline void resizeif(Vector2 point, box& boundbox) {
	if (point.x < boundbox.startpoint.x)
	{
		boundbox.startpoint.x = point.x;
	}
	if (point.y < boundbox.startpoint.y)
	{
		boundbox.startpoint.y = point.y;
	}
	if (point.x > boundbox.endpoint.x)
	{
		boundbox.endpoint.x = point.x;
	}
	if (point.y > boundbox.endpoint.y)
	{
		boundbox.endpoint.y = point.y;
	}
}
inline box::box(polygon poly,Vector2 loc)
{

	*this = box(poly.pointlist[1]+loc, poly.pointlist[2] + loc);
	for (int i = 0; i < poly.pointlist.length; i++)
	{
		resizeif(poly.pointlist[i] + loc,*this);
	}
}  

inline box::box() {


}

inline float box::area()
{
	return (endpoint.x-startpoint.x)* (endpoint.y - startpoint.y);
}
inline bool pointinbox(Vector2 point, box boundbox) {


	if (boundbox.startpoint.x <= point.x && point.x <= boundbox.endpoint.x && boundbox.startpoint.y <= point.y && point.y <= boundbox.endpoint.y)
	{
		return true;
	}
	return false;
}
inline bool box::intersect(box bx)
{
	bool c1 = pointinbox(Vector2(bx.startpoint.x, bx.endpoint.y), *this);
	bool c2 = pointinbox(Vector2(bx.endpoint.x, bx.endpoint.y), *this);
	bool c3 = pointinbox(Vector2(bx.startpoint.x, bx.startpoint.y), *this);
	bool c4 = pointinbox(Vector2(bx.endpoint.x, bx.startpoint.y), *this);
	if (c1||c2||c3||c4)
	{
		return true;
	}
	return false;
}


inline void box::change(Vector2 start, Vector2 end) {



		startpoint = Vector2(min(start.x,end.x), min(start.y, end.y));
		endpoint = Vector2(max(start.x, end.x), max(start.y, end.y));

}
inline void box::changemin(Vector2 start) {



	startpoint = start;
	

}
inline void box::changemax(Vector2 end) {



	endpoint = end;


}
inline box::box(Vector2 start,Vector2 end)
{
	startpoint = Vector2(min(start.x, end.x), min(start.y, end.y));
	endpoint = Vector2(max(start.x, end.x), max(start.y, end.y));
}



#endif