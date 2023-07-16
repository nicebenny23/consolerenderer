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
	triangle();
	void changetriangle(int index, Vector2 point);
 



};

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
inline triangle::triangle()
{
}
#endif 