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


void mainsetup() {

	inittime();
	randominit();
	setbuffer(screensize, ftsize);
	createscreen(screensize.X, screensize.Y, ftsize);
	initobjs();
	userinput::initiate();
	initgravgrid();
	initcol();
	camera::init();
}

int birdamount;
int main()
{
	birdamount = 0;
	mainsetup();

	
	gameobjref dd =gameinit(zerov,unitv,"fprintf.txt","col1test");
	gameobjref dda = gameinit(zerov, unitv, "fprintf.txt", "col1test");


	timer flashtime = timer::timer();
	dd.obj()->addcomponent<collider>();
	dda.obj()->addcomponent<collider>();

	 while (true)
	 {
		 if (userinput::Getkey('m').held)
		 {
		//	 camera::camerapos += userinput::mousestate.pos / 100;

		 }
		 else
		 {
			
		 }
		 camera::cscale = Vector2(1,1);
		userinput::getinput(hIn);
		clearscreen();
	
		if (userinput::Getkey('g').held&&dd.obj()!=nullptr)
		{
			dd.obj()->pos = userinput::mousestate.pos;
		}
	
		
		
	
		runupdateloop();
		checkcol();
		deleteobjs();
		
		drawbox(0, 0, 5, 5, 160);
		
		 drawframe();
			
			 
			 calcfps();
			 calctimers();
			userinput::resetkeys();
		

		 }
	 
	
	
	return 0;
	
}
