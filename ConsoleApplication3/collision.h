#include "gameobject.h"
#include "vector2.h"
#include "polygon.h"
#include "triangle.h"

using namespace gameobject;
using namespace pgon;
#ifndef collision_H
void initcollisionsystem();
void checkcol();
#ifndef coliterations
#define coliterations 3
#endif


struct circle
{
	float radius;
	inline circle() {

		radius = 0;
		center = zerov;
	}
	Vector2 center;
};


struct collider:public component
{
	polygon poly;
	collider(polygon basepoly);
	collider();
	 void update() override;
	 void ondestroy() override;
	 Vector2 storepos;
	 int ind = 0;//each collider has an index 
};
Vector2 computecoll(polygon& a, polygon& b, Vector2 pos1, Vector2 pos2);
Vector2 computeonecoll(polygon& a, polygon& b,Vector2 pos1,Vector2 pos2);


Vector2 collcasework(Vector2 pmax, Vector2 pmin, Vector2 p1max, Vector2 p1min, bool way);


#endif // !collision_H
