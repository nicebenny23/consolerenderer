#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "dynamicarray.h"
#include "vector2.h"

using namespace v2;
using namespace dynamicarray;

namespace pgon{

	class polygon {
		array<Vector2> pointlist;
	public:
		polygon();
		
		Vector2& getelem(int index);
		void insertelement(int index,Vector2 value);
		void append( Vector2 value);
		void drawout(int thickness,COLORREF pixelval);
	};





}






#endif 
