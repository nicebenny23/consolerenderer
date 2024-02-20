#include "vector2.h"
#include <cmath>
#ifndef triangle_hpp
#define triangle_hpp
using namespace v2;
class triangle
{


public:

	Vector2& operator[](int index);
	Vector2 vertices[3];
	triangle(Vector2 trilist[3]);
	triangle(Vector2 a, Vector2 b, Vector2 c);
	triangle();
	void changetriangle(int index, Vector2 point);
	void sortbyheight();



};

inline bool midconvex(triangle tri) {



	Vector2 p1 = tri[0] - tri[1];

	Vector2 p2 = tri[2] - tri[1];
	if (p1.x*p2.y-p2.x*p1.y>0)
	{
		return true;
	}
	return false;
}
inline double ang(int side, triangle tri) {
	double a = distance(tri[0], tri[1]);
	double b = distance(tri[0], tri[2]);
	double c = distance(tri[1], tri[2]);

	switch (side) {
	case 0:
		return acos((b * b + c * c - a * a) / (2 * b * c));

	case 1:
		return acos((a * a + c * c - b * b) / (2 * a * c));

	case 2:
		return acos((a * a + b * b - c * c) / (2 * a * b));

	default:
		return -1.0;
	}
}





inline bool collinear(triangle tri) {

	if (tri[0].x == tri[1].x)
	{
		if (tri[0].x == tri[2].x)
		{
			return true;
		}
		return false;
	}
	if (tri[0].x == tri[2].x)
	{
		if (tri[0].x == tri[1].x)
		{
			return true;
		}
		return false;
	}
	if (slope(tri[0], tri[1]) == slope(tri[0], tri[2]))
	{
		return true;
	}
	return false;
}
inline Vector2 incenter(triangle tri) {
	float a = distance(tri[1], tri[2]);
	float b = distance(tri[0], tri[2]);
	float c = distance(tri[0], tri[1]);

	return(tri[0] * a + tri[1] * b + tri[2] * c) / (a + b + c);
}
inline Vector2 centroid(triangle tri) {




	return (tri[0] + tri[1] + tri[2]) / 3;
}
inline float area(triangle tri) {

	float d = distance(tri[0], tri[1]);
	float d1 = distance(tri[0], tri[2]);
	float d2 = distance(tri[1], tri[2]);
	float sm = (d + d1 + d2) / 2;
	return (sqrt(sm * (sm - d) * (sm - d1) * (sm * d2)));
}




inline void triangle::changetriangle(int index, Vector2 point) {

	vertices[index] = point;

}

inline void triangle::sortbyheight()
{
	Vector2 carry = Vector2(0, 0);
	if (vertices[1].y > vertices[2].y)
	{
		carry = vertices[1];
		vertices[1] = vertices[2];
		vertices[2] = carry;
	}
	if (vertices[0].y > vertices[2].y)
	{
		carry = vertices[0];
		vertices[0] = vertices[2];
		vertices[2] = carry;
	}
	if (vertices[0].y > vertices[1].y)
	{
		carry = vertices[0];
		vertices[0] = vertices[1];
		vertices[1] = carry;
	}
}

inline Vector2& triangle::operator[](int index)
{
	return vertices[index];
}
inline triangle::triangle(Vector2 trilist[3])
{

	for (int i = 0; i < 3; i++)
	{
		vertices[i] = trilist[i];
	}



}
inline triangle::triangle(Vector2 a, Vector2 b, Vector2 c)
{

	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
}
inline triangle::triangle()
{
}
#endif 