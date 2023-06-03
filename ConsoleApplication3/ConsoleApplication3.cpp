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



	void drawline(int px, int py, int p2x, int p2y, COLORREF pixelval) {
		
		
		//for vertical line
 	    if ((px-p2x)==0)
		{
		
			for (int i = min( py,p2y); i <= max(p2y,py); i++)
			{
				d.setpix(px,i,pixelval);
			}
			
				return;
				//no div by zero
		}


		float slope = (static_cast<float>(p2y) - py) / (p2x - px);
		bool uslp = abs(slope) >= 1 ? true : false;
		int startx,starty,endx,endy;
		
		float yconst;
		//make line sorted  by x val and find yconst
		if (p2x > px) {
			startx = px;
			endx = p2x;
			starty = py;
			endy = p2y;
			yconst = py - slope * startx;
		}
		else
		{
			startx = p2x;
			endx = px;
			starty = p2y;
			endy = py;
			yconst = p2y - slope * startx;
		}



	
		
		if (slope > 0)
		{
			//positive slope


			if (uslp)
			{
				//slope greater  than one
				float x = ( (starty - yconst) / slope);
				for (int i = starty; i <= endy; i++)
				{


					
				//use inverse function to get all the points
					d.setpix(round(x+.001), i, pixelval);
					x += 1 / slope;
			
				}
			}




			else
			{
				//slope less tan one

				float y = slope * startx + yconst;
				for (int i = startx; i <= endx; i++)
				{
					//go from start val and increment slope up to end val
					d.setpix(i,std::round( y+.001), pixelval);
					y += slope;
					
				}
			
			}
			
			
		}

		else
		{



			if (uslp)
			{
				float x = (((starty)-yconst) / slope);
				//goes from start  but since we rely on y and y is going down we will decrement instiad  
				for (int i = starty;endy <= i; i--)
				{

					d.setpix(std::round(x - .001), i, pixelval);
					//use y val for func instaid of x val but in this case that would lead to going backwords so *-1
					x -= 1 / slope;
				}
			}


			else
			{
				float y = (slope * (startx)+yconst);
				for (int i = startx; i <= endx; i++)
				{


					//just normal function same things apply

				d.setpix(i, std::round(y + .001), pixelval);
					y += slope;

				}

			}
		}


		}
	//	d.setpix(px, py, White);
	//d.setpix(p2x, p2y, Pink);

	
	
	void drawcircle(int px, int py, int radius, COLORREF pixelColor) {

		
		int prevy = 0;
		int prevx = - radius;
		for(int i = 1-radius; i < floor( - radius / 2); i++)
		{

			int x = prevx + 1;
		short y =short(ceil((std::sqrt(float(radius*radius-i*i)))));

		
		drawline(prevx+px, prevy+py,px+ x, y+py, pixelColor);
		drawline(prevx+px, py-prevy, x+px, py-y, pixelColor);
		drawline(-prevx+px, py - prevy, -x+px, py - y, pixelColor);
		
		drawline(-prevx + px, py + prevy, -x + px, py + y, pixelColor);
		drawline(-prevy + px, py + prevx, -y + px, py + x, pixelColor);
		drawline(prevy + px, py - prevx, y + px, py - x, pixelColor);
		drawline(prevy + px, py + prevx, y + px, py + x, pixelColor);
		drawline(-prevy + px, py - prevx, -y + px, py - x, pixelColor);
			prevx = x;
		prevy = y;
		
	
			//d.setpix(val + px, -val1 +py, pixelColor);
		}
		


	}
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
	
		 drawbox(2, 2, 22,55, Red);
			 auto b = high_resolution_clock::now();
			 auto g = duration_cast<nanoseconds>(b - a).count();
			
			
			

		
		 }
	 
	
	
	return 0;
	
}
