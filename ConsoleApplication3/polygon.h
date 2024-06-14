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
		polygon(const Vector2 initval...);
		polygon(Vector2* listofpoints,int length);
		//makes a copy
		polygon(const polygon& poly);
		Vector2 pos;
		array<Vector2> pointlist;
		
		Vector2 operator[](int index);

		void drawout(int thickness,COLORREF pixelval);
		//deletes polygon
		inline void destroy() {
			
				pointlist.destroy();
			
		}
		inline int length() {

			return pointlist.length;
		}
	};
	polygon convexhull(polygon poly);
	polygon quickerhull(polygon poly);
	bool simple(polygon poly2);
	array<int> numbtri(polygon poly);
	int findindexofpoint(polygon& poly,int startsearch,Vector2 point);
	array<triangle> triangulate(polygon poly);
	bool pointinpolygon(Vector2 point, polygon& poly,bool inpolygonifonsides=false);
	bool nonprecisepointinpolygon(Vector2 point, polygon& poly);
	bool basicintersect(polygon& a, polygon& b);
	float area(polygon poly);
	Vector2 centerofmass(polygon poly);
	bool lineinpolygon(polygon poly,Vector2 start,Vector2 end);

	array<polygon> convexdecomp(polygon poly);

	array<array<int>> trilisttoint(array<int> trilist);
}






#endif 
