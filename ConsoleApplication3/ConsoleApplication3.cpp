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

	
	pg.pointlist.append(Vector2(1, -66));
	pg.pointlist.append(Vector2(60, 55));
	pg.pointlist.append(Vector2(1, 16));
	pg.append(Vector2(-133, -22));

	pg.pointlist.append(Vector2(-94, -84));
	
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
	
		 auto a = high_resolution_clock::now();
		
		 auto b = high_resolution_clock::now();
			 auto g = duration_cast<nanoseconds>(b - a).count();
			 t += g / static_cast<float>(1'000'000);
			
			
			 
		
			 drawframe();
			 userinput::resetkeys();

			
		 }
	 
	
	
	return 0;
	
}
