#include <Windows.h>
#include <stdint.h>

#ifndef mainren_HPP
#define mainren_HPP
namespace Render
{

	 
		
	   extern short Width;
		 extern short Height;
		 extern short hWidth;
		 extern short hHeight;
		 extern COORD Dim;
	
	 extern CHAR_INFO* pixelarray;
		const extern HANDLE* pHout;
	

		
		void createscreen(short startwidth, short startheight, COORD fontsize, const HANDLE* hout);
		void drawframe();
		void setpix(short x, short y, COLORREF col);
	void clearscreen();
	void drawrotbox(short px, short py, int width,int height, float slope, COLORREF pixval);
	void drawbox(short px, short py, int width, int height, COLORREF pixval);
	void drawline(int px, int py, int p2x, int p2y, COLORREF pixelval);
	void drawthickline(int px, int py, int p2x, int p2y,int thickness, COLORREF pixelval);
	void drawthickcircle(int px, int py, int radius, int thickness, COLORREF pixelval);
	void drawcircle(int px, int py, int radius, COLORREF pixelColor);
		 COORD GetDim();
		
		
	
	







}
#endif;
