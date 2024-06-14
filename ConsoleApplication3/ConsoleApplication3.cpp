     #include <string>
#include "btree.h"
#include <iostream>

#include <chrono>
#include "Renderer.h"
#pragma warning(disable: 4996)
#include <Windows.h>
#include "screenset.h"
#include "gametime.h"
#include "collision.h"
#include "Colorinfo.h"
#include "dynamicarray.h"
#include "polygon.h"
#include "dsprite.h"
#include "ant.h"
#include "userinput.h"
#include "random.h"
#include "safearray.h"
#include "camera.h"
#include "debug.h"
#include "spriterender.h"
#include "gameobject.h"
using namespace spritename;
using namespace Render;
using namespace Color;
using namespace std::chrono;
using namespace saferarray;
using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;
using namespace gameobject;
char* num;








const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
static COORD screensize = { 800,800 };
static COORD ftsize = { 2,2 };


void enginesetup() {

	inittime();
	randominit();
	setbuffer(screensize, ftsize);
	createscreen(screensize.X, screensize.Y, ftsize);
	initobjs();
	userinput::initiate();
	initgravgrid();
	initcollisionsystem();
	camera::init();
}

int birdamount;
int main()
{
	debug::reset();
	std::string string = "debugging:         ";
	debug::writestring(string);
	Vector2 a[] = { Vector2(-3, 0), Vector2(-3, 3), Vector2(0,0)};




	enginesetup();
	int l = 0;

	gameobjref dd =gameinit(Vector2(-0,-3), unitv, "fprintf.txt", "col1test");
	
	Vector2 movepos = zerov;
	gameobjref ddc = gameinit(Vector2(-100,-150), unitv, "fprintf.txt", "col1test");
	timer flashtime = timer::timer();
	dd.obj()->addcomponent<collider>();
	ddc.obj()->addcomponent<collider>(polygon(a,3));

	while (true)
	 {
		
		
	
		
		 camera::cscale = Vector2(1,1);
		userinput::getinput(hIn);
		if (userinput::Getkey('t').pressed)
		{
			l = 0;
			ddc.obj()->pos = Vector2(0, 0);
		}
		clearscreen();
		
		if (dd.obj() != nullptr)
		{
			movepos.x *= .81;
			movepos.y *= .81;
			if(userinput::Getkey('a').held)
			{
				movepos -= Vector2(4, 0);
			}
			if (userinput::Getkey('d').held)
			{
				movepos += Vector2(4, 0);
			}if (userinput::Getkey('w').held)
			{
				movepos.y +=4;
			}
		if (userinput::Getkey('s').held)
		{
			movepos.y -=4;
		}
			
			
				dd.obj()->pos +=movepos/4;
			
			
			
		}
		if (lineinter(Vector2(3,3), Vector2(5,3),Vector2(3,3),Vector2(5,3)))
		{
			drawbox(0, 0, 60, 40, 16);
				drawbox(0, 0, fps, 40, 80);
		}
	
		
		drawbox(0, 0, 5, fps, 160);
		runupdateloop();

		checkcol();
		deleteobjs();
		
		
		
		
		
		drawframe();
		
			 calcfps();

			 calctimers();
			userinput::resetkeys();
		

		 }
	 
	
	
	return 0;
	
}
