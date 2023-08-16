#include "camera.h"
#include "vector2.h"

Vector2 camera::camerapos;
Vector2 camera::cscale;
 void camera::init() {



	camerapos = Vector2(0, 0);
	cscale = Vector2(1, 1);


}

 
inline bool camera::inbounds(Vector2 loc, float xdim, float ydim) {

	Vector2 dim = Render::GetDim();
	float dmx = (cscale.x * dim.x) / 2;
	float dmy = (cscale.y * dim.y) / 2;

	float xd2 = xdim / 2;
	float yd2 = ydim / 2;
	Vector2 pnt = loc - camerapos;
	if (pnt.x + xd2<dmx && pnt.x - xd2 > -dmx)
	{
		if (pnt.y + yd2<dmy && pnt.y - yd2 > -dmy)
		{
			return true;

		}

	}

	return false;


}