#include <Windows.h>
#include <stdint.h>

#ifndef mainren_HPP
#define mainren_HPP
namespace Render
{

	 static class Screen
	{
	
		
	     short Width;
		 short Height;
		 int hWidth;
		 int hHeight;
		 COORD Dim;
	
	 CHAR_INFO* pixelarray;
		const HANDLE* pHout;
	
	public:
		
		Screen(short startwidth, short startheight, COORD fontsize, const HANDLE* hout);
		void drawframe();
		void setpix(short x, short y, COLORREF col);
	void clearscreen();
	void drawline(int px, int py, int p2x, int p2y, COLORREF pixelval);
		 COORD GetDim();
		
		
	};
	







}
#endif;
