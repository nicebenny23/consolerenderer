  #include <string>
#include<windows.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "Renderer.h"
#include "Colorinfo.h"
#include "screenset.h"
#include <cmath>;
using namespace Render;
using namespace Color;
using namespace std::chrono;
namespace drawfunc {

	
	
	
}
using namespace Render;	
using namespace drawfunc;
using namespace std::chrono;


using namespace winutil;
int main()
{
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	static COORD screensize = { 800,800 };
	static COORD ftsize = { 2,2 };


	
	static Pallete pallete;

	setmode(hIn);
	setcursor(hOut);
	setfont(ftsize, hOut);
	 setbuffer(screensize,ftsize,hOut);
	

	
	
	
	createscreen(screensize.X, screensize.Y, ftsize, &hOut);
	 int h=1;
	 while (true)
	 {

	
		 h++;
		clearscreen();
		 auto a = high_resolution_clock::now();
		 drawline(2, 2, 33, 4, Red);
		 drawline(2, 2, 521,511, Blue);
			 auto b = high_resolution_clock::now();
			 auto g = duration_cast<nanoseconds>(b - a).count();
			
			
			 drawframe();

		
		 }
	 
	
	
	return 0;
	
}
