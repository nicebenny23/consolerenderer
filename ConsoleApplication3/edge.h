#include "vector2.h"
using namespace v2;
#ifndef line_HPP
#define line_HPP

namespace line {
	struct line
	{

		Vector2 point1;
		Vector2 point2;
		line(float x, float y, float x1, float y1);

	};
	line::line(float x, float y, float x1, float y1)
	{

		point1 = Vector2(x, y);

		point2 = Vector2(x1, y1);
	}
}
#endif // !line_HPP
