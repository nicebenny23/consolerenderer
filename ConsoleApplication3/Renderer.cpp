#include <Windows.h>
#include "Renderer.h"
#include "Colorinfo.h"
#include <cmath>

namespace Render {


	short Width;
	short Height;
	short hWidth;
	short hHeight;
	COORD Dim;

	CHAR_INFO* pixelarray;
	const HANDLE* pHout;
	void createscreen(short startwidth, short startheight, COORD fontsize, const HANDLE* hout)
	{

	

		 Width = 2 * round(startwidth / (2 * fontsize.X));
	Height = 2 * round(startheight / (2 * fontsize.Y));
		 pHout = hout;
	
		 hWidth = (Width / 2);
			hHeight = (Height / 2);
		 Dim = { Width,Height };

		pixelarray = new CHAR_INFO[Width * Height];
		clearscreen();
	}

	void clearscreen() {






		for (int i = 0; i < Width * Height; i++)
		{
			pixelarray[i].Attributes = BLACK;

			pixelarray[i].Char.UnicodeChar = ' ';
		}


	}

	COORD GetDim()
	{
		return Dim;
	}

	void drawframe() {


		COORD ScreenBufferCoord = { 0, 0 };
		SMALL_RECT ConsoleCoord = { 0, 0, Width, Height };

		WriteConsoleOutputA(*pHout, pixelarray, Dim, ScreenBufferCoord, &ConsoleCoord);

	}

	void setpix(short x, short y, COLORREF col) {

		if (  abs(x) < hWidth && abs(y) < hHeight) {

			CHAR_INFO* pix = &pixelarray[Width * ((hHeight - y)) + ((x + hWidth))];
			(*pix).Char.UnicodeChar = ' ';
			(*pix).Attributes = col;

		}
	}







	void drawbox(short px, short py, int width, int height, COLORREF pixval) {








		short voff = (py - ceil(height/2));
		short vpff = (py + ceil(height/2));
		short hoff = (px - ceil(width/2));
		short hpoff = (px + ceil(width/2));
		for (short i = hoff; i < hpoff; i++)
		{
			for (short j = voff; j < vpff; j++)
			{

				setpix(i, j, pixval);
			}
		}





	
}






	void drawcircle(int px, int py, int radius, COLORREF pixelColor) {


		int prevy = 0;
		int prevx = -radius;
		for (int i = 1 - radius; i < floor(-radius / 2); i++)
		{

			int x = prevx + 1;
			short y = short(ceil((std::sqrt(float(radius * radius - i * i)))));


			drawline(prevx + px, prevy + py, px + x, y + py, pixelColor);
			drawline(prevx + px, py - prevy, x + px, py - y, pixelColor);
			drawline(-prevx + px, py - prevy, -x + px, py - y, pixelColor);

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



















	void drawline(int px, int py, int p2x, int p2y, COLORREF pixelval) {


		//for vertical line
		if (px - p2x == 0)
		{

			for (int i = min(py, p2y); i <= max(p2y, py); i++)
			{
				setpix(px, i, pixelval);
			}

			return;
			//no div by zero
		}


		float slope = (static_cast<float>(p2y) - py) / (p2x - px);
		
		bool uslp = abs(slope) >= 1 ? true : false;
		int startx, starty, endx, endy;

		float yconst;
		//make line sorted  by x val and find yconst
		if (p2x > px) {
			startx = px;
			endx = p2x;
			starty = py;
			endy = p2y;
			
		}
		else
		{
			startx = p2x;
			endx = px;
			starty = p2y;
			endy = py;
		
		}
		yconst = starty - slope * startx;




		if (slope > 0)
		{
			//positive slope


			if (uslp)
			{
				//slope greater  than one
				float x = ((starty - yconst) / slope);
				for (int i = starty; i <= endy; i++)
				{



					//use inverse function to get all the points
					setpix(round(x + .001), i, pixelval);
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
					setpix(i, std::round(y + .001), pixelval);
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

					setpix(std::round(x - .001), i, pixelval);
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

					setpix(i, std::round(y + .001), pixelval);
					y += slope;

				}

			}
		}


	}
	











	void drawthickline(int px, int py, int p2x, int p2y,int thickness, COLORREF pixelval) {


		//for vertical line
		if (px - p2x == 0)
		{

			for (int i = min(py, p2y); i <= max(p2y, py); i++)
			{
				drawbox(px, i,thickness,thickness, pixelval);
			}

			return;
			//no div by zero
		}
	
		float slope = (static_cast<float>(p2y) - py) / (p2x - px);
		int ofsetx = thickness / 2 * sqrt(slope * slope + 1);
		int ofsety = slope*ofsetx;
		bool uslp = abs(slope) >= 1 ? true : false;
		int startx, starty, endx, endy;
		
		float yconst;
		//make line sorted  by x val and find yconst
		if (p2x > px) {
			startx = px;
			endx = p2x;
			starty = py;
			endy = p2y;

		}
		else
		{
			startx = p2x;
			endx = px;
			starty = p2y;
			endy = py;

		}

		if (uslp)
		{

		}
		else {


		}


		if (slope > 0)
		{
			//positive slope
			
			
			yconst = starty - slope * startx;
			if (uslp)
			{
				//slope greater  than one
				
				
				float x = ((starty - yconst) / slope);
				for (int i = starty; i <= endy; i++)
				{



					//use inverse function to get all the points
					for (int j = -thickness/2; j <= thickness/2; j++)
					{
						setpix(round(x +j), i, pixelval);
					}
				
					x += 1 / slope;

				}
			}




			else
			{
			
				
				//slope less than one
				yconst = starty - slope * startx;



			
				
				float y = slope * (startx) + yconst;
				for (int i = startx; i <= endx; i++)
				{
					//go from start val and increment slope up to end val
					for (int j =  - thickness / 2; j <= thickness / 2; j++)
					{


						setpix(i, std::round(y)+j,pixelval);
					}
					y +=slope;

				}

			}


		}

		else
		{

		

			if (uslp)
			{
				
			
				yconst = starty - slope * startx;
				float x = (((starty)-yconst) / slope);
				//goes from start  but since we rely on y and y is going down we will decrement instiad  
				for (int i = starty;endy <= i; i--)
				{
					for (int j = -(thickness/2); j <= thickness/2; j++)
					{
						setpix(std::round(x)+j, i,pixelval);
					}
					
					//use y val for func instaid of x val but in this case that would lead to going backwords so *-1
					x -= 1/ slope;
				}
			}


			else
			{
				
				yconst = starty - slope * startx;
				float y = (slope * (startx)+yconst);
				for (int i = startx; i <= endx; i+=1)
				{


					//just normal function same things apply
					for (int j = -thickness/2; j <= thickness/2; j++)
					{
						setpix(i, std::round(y )+j, pixelval);
					}
				
					y +=slope;

				}

			}
		}


	}





	void drawthickcircle(int px, int py, int radius,int thickness, COLORREF pixelColor) {


		int prevy = 0;
		int prevx = -radius;
		for (int i = 1 - radius; i <= ceil(-radius / 2); i+=1)
		{

			int x = prevx + 1;
			short y = short(ceil((std::sqrt(float(radius * radius - i * i)))));


			drawthickline(prevx + px, prevy + py, px + x, y + py, thickness,pixelColor);
			drawthickline(prevx + px, py - prevy, x + px, py - y, thickness, pixelColor);
			drawthickline(-prevx + px, py - prevy, -x + px, py - y, thickness, pixelColor);

			drawthickline(-prevx + px, py + prevy, -x + px, py + y, thickness, pixelColor);
			drawthickline(-prevy + px, py + prevx, -y + px, py + x, thickness, pixelColor);
			drawthickline(prevy + px, py - prevx, y + px, py - x, thickness, pixelColor);
			drawthickline(prevy + px, py + prevx, y + px, py + x, thickness, pixelColor);
			drawthickline(-prevy + px, py - prevx, -y + px, py - x, thickness, pixelColor);
			prevx = x;
			prevy = y;


			//d.setpix(val + px, -val1 +py, pixelColor);
		}



	}





}