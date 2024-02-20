#include "gameobject.h"
#include "vector2.h"
#include "polygon.h"
#include "triangle.h"

using namespace gameobject;
using namespace pgon;
#ifndef collision_H
void initcol();
void checkcol();
struct collider:public component
{
	polygon poly;
	collider(polygon basepoly);
	collider();
	 void update() override;
	 void ondestroy() override;
	 int ind = 0;//each collider has an index 
};

Vector2 computeonecoll(polygon& a, polygon& b,Vector2 pos1, Vector2 pos2);

Vector2 computecoll(polygon& a, polygon& b,Vector2 pos1,Vector2 pos2);



#endif // !collision_H
