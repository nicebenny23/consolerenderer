  #include <string>

#include <iostream>

#include <chrono>
#include "Renderer.h"
#include <Windows.h>
#include "screenset.h"
#include "Colorinfo.h"
#include "dynamicarray.h"
#include "polygon.h"
#include "userinput.h"
#include "random.h"
using namespace Render;
using namespace Color;
using namespace std::chrono;

using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;
int main()
{
	srand((unsigned)(time)(0));
	array<int> a = array<int>(4);
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	static COORD screensize = { 800,800 };
	static COORD ftsize = { 2,2 };



	v2::Vector2 vbo = v2::Vector2(2, 2);

	SetConsoleTitleA("console render");
	setmode(hIn);
	setcursor(hOut);
	setfont(ftsize, hOut);
	setbuffer(screensize, ftsize, hOut);



	polygon pg = polygon();
	createscreen(screensize.X, screensize.Y, ftsize, &hOut);
	pg.pointlist.append(Vector2(-44, -84));
	pg.append(Vector2(4, -144));
	pg.pointlist.append(Vector2(60, 55));
	pg.pointlist.append(Vector2(1, 166));
	Vector2 morb[3] = { Vector2(-22, -22), Vector2(33, 33), Vector2(354,54) };

triangle tri = triangle(morb);
	 userinput::initiate();
	
	 v2::Vector2 d = v2::Vector2(2, 2);
	 float t=1;
	 int g = 1;
	 int p = 1;
	 int th = 1;
	 init();
	 while (true)
	 {
		
		userinput::getinput(hIn);
		clearscreen();
		
	
		if (userinput::Getkey('r').held)
		{
			pg.pointlist.deleteind(pg.pointlist.length-1);
		}
		Vector2 polymass = pgon::centerofmass(pg);
		pg.pointlist[0] = polymass;

		//drawthickcircle2(0, 0, 55, th ,Blue);
	//	drawbox(round(userinput::mousestate.pos.x),round( userinput::mousestate.pos.y), 4, 41, col(6));
			d += v2::Vector2(.5, 3*cos(v2::distance(d,v2::zerov)));
		//setpix(44, 102, Red);
	
		// drawline(2, 2, 33, 4, Red);
	
		//drawlinet(22, 22, 33, 44,44, Green);
		
			
		 auto a = high_resolution_clock::now();
		 if (randombool()) {
			 for (int i = 0; i < 8; i++)
			 {

				

			 }
			 float ga = 0;
		 }
		 pg.drawout(5,128);
			int l = random() * 15;
			tri[2] = userinput::mousestate.pos;
			pg.polypos = userinput::mousestate.pos-polymass;
		//	pg.drawout(4, 16);
		//	drawbox(polymass.x, polymass.y, 22, 22, 240);
			 auto b = high_resolution_clock::now();

			 auto g = duration_cast<nanoseconds>(b - a).count();
			 t += g / static_cast<float>(1'000'000);
			 drawframe();
			 userinput::resetkeys();
		 }
	 
	
	
	return 0;
	
}
