#pragma once
#include "vector2.h"
#include "gameobject.h"
using namespace v2;
using namespace gameobject;
#ifndef ant_HPP
#define ant_HPP




void initgravgrid();

	



struct gravobj : component
{
	gravobj(Vector2 pos,float mass2);
	void start() override;
	void update() override;
	float mass;
	Vector2 ac;
	Vector2 vel;
	int ind;
	Vector2 posstore;
};


#endif // !ant
