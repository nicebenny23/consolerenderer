
#include "Renderer.h"
#include "Colorinfo.h"


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

		if (  x < hWidth&& x > -hWidth && y < hHeight && y > -hHeight) {

			CHAR_INFO* pix = &pixelarray[Width * ((hHeight - y)) + x + hWidth];
			pix->Char.UnicodeChar = ' ';
			pix->Attributes = col;

		}
	}







	void drawbox(short px, short py, int width, int height, COLORREF pixval) {



	




		short voff = (py - floor(height/2));
		short vpff = (py + floor(height/2));
		short hoff = (px - floor(width/2));
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
















	void drawlinet(v2::Vector2 v1, v2::Vector2 v2,int thickness, COLORREF pixelcol) {
		drawlinet(round(v1.x), round(v1.y), round(v2.x),round( v2.y), thickness, pixelcol);	
	}

	void drawline(int x, int y, int x1, int y1, COLORREF pixelcol)
	{
		
		int dx = abs(x - x1);
		int sx = x <= x1 ? 1 : -1;
		int dy = abs(y1 - y);
		int sy = y <= y1 ? 1 : -1;
		
		int error = dx - dy;

		for (;;) {




			setpix(x, y, pixelcol);
			if (x == x1 && y == y1) {
				return;
			}
			int e2 = 2 * error;
			if (e2 >= -dy) {


				error -= dy;
				x += sx;
			}
			if (e2 <= dx) {

				error = error + dx;
				y += sy;

			}
		}

	}
	void drawlinet(int x0, int y0, int x1, int y1,float thickness, COLORREF pixelcol)
	{

	//dont really understand how this works will learn later
		 
		drawthickcircle(x0, y0, thickness, pixelcol);
		drawthickcircle(x1, y1, thickness, pixelcol);
		
		if (x0-x1 == 0 || y0-y1 == 0)
		{

			if (x0-x1 == 0)
			{
				drawbox(x0, ((y0 + y1) / 2),  2*thickness+1, round(abs(y1 - y0)), pixelcol);
			}
			else {

				drawbox((x0 + x1) / 2, (y0 + y1) / 2, abs(x1 - x0), 2*thickness, pixelcol);

			}
			return;
		}

		
		int sx = (x1 >= x0) ? 1 : -1;
		int sy = ((y1 >= y0)) ? 1 : -1;
		  
		
		int p_error = 0;
		int error = 0;
		int y = y0;
		int x = x0;
		int dx = abs(x1 - x);
		int dy = abs(y1 - y);
		int sdx = x1 - x;
		int sdy = (y1 - y);
	
	
		
		int dist = sqrt(dx * dx + dy + dy);
		
		if (dx>=dy)
		{
			 int threshold = dx - 2 * dy;
			int E_diag = -2 * dx;
			int E_square = 2 * dy;
			int length = dx+1;
			for (int i = 0; i < length; i++)
			{
			
				perpxsub(x, y, sdx, sdy, p_error, thickness, error,pixelcol);

				if (error >= threshold)
				{
					y += sy;
					error = error + E_diag;
					if (p_error >= threshold)
					{
						perpxsub(x, y, sdx, sdy, p_error+E_diag + E_square, thickness, error,pixelcol);

						p_error += E_diag;

					}

					p_error += E_square;

				}
				error += E_square;
				x += sx;
				
			}
			
		}
		else {

			
				int threshold = dy - 2 * dx;
				int E_diag = -2 * dy;
				int E_square = 2 * dx;
				int length = dy+1;
				for (int i = 0; i < length; i++)
				{
					
					perpysub(x, y, sdx, sdy, p_error, thickness, error,pixelcol);

					if (error >= threshold)
					{
						x += sx;
						error = error + E_diag;
						if (p_error >= threshold)
						{
							perpysub(x, y, sdx, sdy, p_error + E_diag + E_square, thickness, error, pixelcol);

							p_error += E_diag;

						}

						p_error += E_square;

					}
					error += E_square;
					y += sy;
					
				}
				
		
		}
		//implement check
		
	}

	void perpxsub(int x0, int y0, int sdx, int sdy, int einit, int width, int winit,COLORREF pixelcol) {


		int dx = abs(sdx);
		int dy = abs(sdy);
		int sx = sdx >= 0 ? 1 : -1;
		int sy = sdy >= 0 ? 1 : -1;
		int x = x0;
		int y = y0;
		int E_diag = -2 * dx;
		int E_square = 2 * dy;
		int threshold = dx - 2 * dy;
		float wthr = 2 *width * sqrt(dx * dx + dy * dy);
	
		int error = einit;
		int tk = dx + dy - winit;
		while (tk <= wthr)
		{


			setpix(x, y,pixelcol);

			if (error >  threshold)
			{
				x -= sx;

				error += E_diag;
				tk += 2 * dy;
			}

			error = error + E_square;
			y += sy;
			tk += 2 * dx;

		}
		x = x0;
		y = y0;
		error = -einit;
		tk = dx + dy + winit;
		while (tk <= wthr)
		{


			setpix(x, y,pixelcol);

			if (error > threshold)
			{
				x += sx;

				error += E_diag;
				tk += 2 * dy;
			}

			error = error + E_square;
			y -= sy;
			tk += 2 * dx;

		}
	}


	void perpysub(int x0, int y0, int sdx, int sdy, int einit, int width, int winit,COLORREF pixelcol) {


		int dx = abs(sdx);
		int dy = abs(sdy);
		int sx = sdx >= 0 ? 1 :-1;
		int sy = sdy >= 0 ? 1 : -1;
		int x = x0;
		int y = y0;
		
		int E_diag = -2 *  dy;
		int E_square = 2 * dx;
		int threshold = dy - 2 * dx;
		float wthr = 2 * width * sqrt(dx * dx + dy * dy);
		int error = einit;
		int tk = dx + dy - winit;
		while (tk <= wthr)
		{

				setpix(x, y, pixelcol);
			
			if (error>threshold)
			{
				y-=sy;
				
				error += E_diag;
				tk += 2 * dx;
			}
			
			error = error + E_square;
				x +=sx;
				tk += 2 * dy;
			
		}
		x = x0;
			y=y0;
		error = -einit;
		tk = dx + dy + winit;
		while (tk <= wthr)
		{
			

			setpix(x, y, pixelcol);

			if (error > threshold)
			{
				y+=sy;

				error += E_diag;
				tk +=  2 * dx;
			}

			error = error + E_square;
			x -=sx;
			tk += 2 * dy;
			
		}
		
	}
		
	void drawthickcircle(short px, short py, short radius, COLORREF pixelval) {
		short y = 0;
		
		for (int i = - radius; i <=0; i++)
		{
			
			y=short(sqrt(radius * radius - i * i));
			for (short j = 0; j < y; j++)
			{
				setpix(i + px, j + py, pixelval);
				setpix(-i + px, j + py, pixelval);
				setpix(i + px, -j + py, pixelval);
				setpix(-i + px, -j + py, pixelval);
			}
			
		}




	}




	void drawthickcircle2(int px, int py, int radius,int thickness, COLORREF pixelColor) {


		int prevy = 0;
		int prevx = -radius;
		for (int i = 1 - radius; i < floor(-radius / 2); i++)
		{

			int x = prevx + 1;
			short y = short(ceil((std::sqrt(float(radius * radius - i * i)))));

			drawlinet(prevx + px, prevy + py, px + x, y + py,thickness, pixelColor);
			drawlinet(prevx + px, py - prevy, x + px, py - y,thickness, pixelColor);
			drawlinet(-prevx + px, py - prevy, -x + px, py - y,thickness, pixelColor);

			drawlinet(-prevx + px, py + prevy, -x + px, py + y,thickness, pixelColor);
			drawlinet(-prevy + px, py + prevx, -y + px, py + x,thickness, pixelColor);
			drawlinet(prevy + px, py - prevx, y + px, py - x,thickness, pixelColor);
			drawlinet(prevy + px, py + prevx, y + px, py + x,thickness, pixelColor);
			drawlinet(-prevy + px, py - prevx, -y + px, py - x,thickness, pixelColor);
			prevx = x;
			prevy = y;
			
			//d.setpix(val + px, -val1 +py, pixelColor);
		}




	}





}
