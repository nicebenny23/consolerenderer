#include "vector2.h"
#ifndef triangle_hpp
#define triangle_hpp
using namespace v2;
class triangle
{

	
public:
	
	Vector2& operator[](int index);
	Vector2 vertices[3];
	triangle(Vector2 trilist[3]);
	triangle(Vector2 a,Vector2 b,Vector2 c);
	triangle();
	void changetriangle(int index, Vector2 point);
	



};



inline bool collinear(triangle tri) {

	if (tri[0].x==tri[1].x)
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
	if (slope(tri[0],tri[1])==slope(tri[0],tri[2]))
	{
		return true;
	}
	return false;
}
inline Vector2 incenter(triangle tri) {
	float a =distance(tri[1], tri[2]);
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
	float sm= (d + d1 + d2) / 2;
	return (sqrt(sm * (sm - d) * (sm - d1) * (sm * d2)));
}




inline void triangle::changetriangle(int index,Vector2 point) {

	vertices[index] = point;

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