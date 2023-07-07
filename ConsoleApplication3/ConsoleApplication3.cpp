  #include <string>

#include <iostream>

#include <chrono>
#include "Renderer.h"
 
#include "screenset.h"
#include "Colorinfo.h"
#include "dynamicarray.h"
#include "polygon.h"
using namespace Render;
using namespace Color;
using namespace std::chrono;
namespace drawfunc {

	
	
	
}
using namespace Render;	
using namespace drawfunc;
using namespace std::chrono;

using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;
int main()
{
	array<int> a = array<int>(4);
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	static COORD screensize = { 800,800};
	static COORD ftsize = { 2,2};


	
	v2::Vector2 vbo=	v2::Vector2(2, 2);
	
	
	setmode(hIn);
	setcursor(hOut);
	setfont(ftsize, hOut);
	 setbuffer(screensize,ftsize,hOut);
	

	
	 polygon p = polygon();
	 createscreen(screensize.X, screensize.Y, ftsize, &hOut);
	 p.append(Vector2(-88, -0));
	 p.append(Vector2(88, 88));
	 p.insertelement(1, Vector2(-88,88));
	
	
	 v2::Vector2 d = v2::Vector2(2, 2);
	 float t=1;
	 while (true)
	 {

		
		 
		clearscreen();
			d += v2::Vector2(.5, 3*cos(v2::distance(d,v2::zerov)));
		//setpix(44, 102, Red);
		 auto a = high_resolution_clock::now();
		// drawline(2, 2, 33, 4, Red);
		
		 p.drawout(4, Red);
		//drawlinet(22, 22, 33, 44,44, Green);
		
			 auto b = high_resolution_clock::now();
			 auto g = duration_cast<nanoseconds>(b - a).count();
			 t += g / static_cast<float>(1'000'000);
			 //drawlinet(22, 33, 44, t,t, Red);
			
			
			 drawframe();

		
		 }
	 
	
	
	return 0;
	
}
