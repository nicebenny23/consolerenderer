#include <Windows.h>
#include <stdint.h>
#include "vector2.h"
#include "triangle.h"
#ifndef mainren_HPP

#define mainren_HPP
namespace Render
{

	 

	   
		
	
		const extern HANDLE* pHout;
	

		void createscreen(short startwidth, short startheight, COORD fontsize);
		void drawframe();
		void setpix(int x, int	y, DWORD col);
		void settpix(int x, int y, DWORD col, char opacity);
		
		DWORD getpix(int x, int	y);
		DWORD unsafegetpix(int x, int y);
		void unsafesetpix(int x, int y, DWORD col);
	void clearscreen();

	void drawtriangle(triangle tri, DWORD col);
	void drawlinet(v2::Vector2 v, v2::Vector2 v2, int thickness, COLORREF pixelcol);
	void drawbox(short px, short py, int width, int height, COLORREF pixval);
	void drawline(int px, int py, int p2x, int p2y, COLORREF pixelval);
	void drawthickcircle(short px, short py, short radius, COLORREF pixelval);
	void drawlinet(int px, int py, int p2x, int p2y,float thickness, COLORREF pixelval);  //not mine as i could not come up with my own algorthm 
	void perpxsub(int x0, int y0, int dx, int dy, int einit, int width, int winit,COLORREF pixelcol);//part of draw line t
	void perpysub(int x0, int y0, int sdx, int sdy, int einit, int width, int winit,COLORREF pixelcol); //part of draw line t
	void drawthickcircle2(int px, int py, int radius, int thickness, COLORREF pixelval);
	void drawcircle(int px, int py, int radius, COLORREF pixelColor);
v2::Vector2 GetDim();
		
		
	
	







}
#endif;
