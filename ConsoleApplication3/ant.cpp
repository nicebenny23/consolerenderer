#include "ant.h"
#include "spriterender.h"
#include "random.h"
#include "Renderer.h"
#include "oalgorithm.h"
#include "userinput.h"
#include "triangle.h"
#include "camera.h"
array<gameobjref> gravlist;
void initgravgrid()
{
	gravlist = array<gameobjref>(); 

}



gravobj::gravobj(Vector2 pos, float mass2)
{
	posstore = pos;
	mass = mass2;
}

void gravobj::start()
{
	
	holder->pos = posstore;
	ind = gravlist.length;
	vel = Vector2(random()-.5f, random()-.5f)*10;
	gravlist.append(gameobjref(*holder));
}

Vector2 movforce(int ind) {
	Vector2 force = zerov;
	gameobj* thisobj = gravlist[ind].obj();
	for (int i = 0; i < gravlist.length; i++)
	{
		if (i != ind) {

			gameobj* obj = gravlist[i].obj();
			gravobj s = obj->getcomponent<gravobj>();
			float dist = distance(obj->pos, thisobj->pos);
			if (dist!=0)
			{
				force += normal(obj->pos - thisobj->pos) * s.mass / (dist * dist);

			}
			
				
			
			
		}


	}
	return force;
}


void gravobj::update()
{

	holder->pos = posstore;

	ac =clampmag( movforce(ind),11);
	

		vel += ac;

		posstore += vel/100;
	
		
	
	
		gameobj& l = *holder;
	
	spriterenderer::drawtoscreen(l,norm);
}
