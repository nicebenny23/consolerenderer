#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "dynamicarray.h"
#include "vector2.h"

#include "triangle.h"
using namespace v2;
using namespace dynamicarray;

namespace pgon{

	class polygon {
		
	public:
		void append(Vector2 val);

		
		polygon();
		polygon(Vector2* listofpoints,int length);
		polygon(const polygon& poly);
		Vector2 polypos;
		array<Vector2> pointlist;
		Vector2 operator[](int index);

		void drawout(int thickness,COLORREF pixelval);
	};
	polygon convexhull(polygon poly);
	polygon quickerhull(polygon poly);
	bool simple(polygon poly2);
	array<int> numbtri(polygon poly);
	array<triangle> triangulate(polygon poly);
	bool pointinpolygon(Vector2 point, polygon poly);
	float area(polygon poly);
	Vector2 centerofmass(polygon poly);
	bool lineinpolygon(polygon poly,Vector2 start,Vector2 end);

	array<polygon> convexdecomp(polygon poly);

	array<array<int>> trilisttoint(array<int> trilist);
}






#endif 
