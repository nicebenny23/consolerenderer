#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "dynamicarray.h"
#include "vector2.h"
#include "boxflt.h"
#include "triangle.h"
using namespace v2;
using namespace dynamicarray;

namespace pgon{

	class polygon {
		
	public:
		void append(Vector2 val);

		
		polygon();
		polygon(Vector2* listofpoints,int length);
		array<triangle> triangulate;
		Vector2 polypos;
		array<Vector2> pointlist;
		box boundingbox;
		void drawout(int thickness,COLORREF pixelval);
	};
	float area(polygon poly);
	Vector2 centerofmass(polygon poly);



}






#endif 
