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

	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	static COORD screensize = { 800,800 };
	static COORD ftsize = {5,5 };
	 

	Screen d = Screen(screensize.X, screensize.Y, ftsize, &hOut);
	static Pallete pallete;


	void drawbox(int px, int py, int width, int height,COLORREF pixval) {






	
		
		short voff = (py-(height / 2));
		short vpff = (py + (height / 2));
		short hoff = (px - (width / 2));
		short hpoff = (px + (width / 2));
		for (short i =  hoff; i < hpoff; i++)
		{
			for (short j = voff; j < vpff; j++)
			{
  
				d.setpix(i,  j, pixval);
			}
		}




		//std::cout << prevy;
	}



	//	d.setpix(px, py, White);
	//d.setpix(p2x, p2y, Pink);

	
	
	
}
using namespace Render;	
using namespace drawfunc;
using namespace std::chrono;

using namespace Color;
using namespace winutil;
int main()
{
	
	setmode(hIn);
	setcursor(hOut);
	setfont(ftsize, hOut);
	 setbuffer(screensize,ftsize,hOut);
	

	
	
	
	
	 int h=1;
	 while (true)
	 {
		
		d.drawframe();
		 h++;
		d.clearscreen();
		 auto a = high_resolution_clock::now();
		 d.drawline(2, 2, 33, 4, Red);
		 drawbox(2, 2, 22,55, Red);
			 auto b = high_resolution_clock::now();
			 auto g = duration_cast<nanoseconds>(b - a).count();
			
			
			

		
		 }
	 
	
	
	return 0;
	
}
