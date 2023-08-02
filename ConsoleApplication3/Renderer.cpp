
#include "Renderer.h"
#include "Colorinfo.h"
#include "random.h"

namespace Render {


	int  Width;
	int Height;
	int hWidth;
	int hHeight;
int	cval;//for speed
v2::Vector2 Dim;
COORD Dimval;
	
	CHAR_INFO* pixelarray;
	const HANDLE* pHout;
	void createscreen(short startwidth, short startheight, COORD fontsize, const HANDLE* hout)
	{

	

		 Width = 2 * round(startwidth / (2 * fontsize.X))+1;
	Height = 2 * round(startheight / (2 * fontsize.Y))+1;
		 pHout = hout;
		
		 hWidth = (Width / 2);
			hHeight = (Height / 2);
			Dim = Vector2(Width, Height);
		 Dimval = { short(Width),short(Height) };
		
		pixelarray = new CHAR_INFO[Width * Height];
		clearscreen();
		cval= (Width * hHeight) + hWidth;
	}





	//safe method to set pix
inline	void setpix(const int x, const int y, DWORD col) {
		
		
		if (y <= hHeight && y >= -hHeight&&  x <= hWidth&& x >= -hWidth) {
			pixelarray[x -(Width * y)+cval ].Attributes =col;
			
		}
	}

DWORD getpix(int x, int y)
{



	if (y <= hHeight && y >= -hHeight && x <= hWidth && x >= -hWidth) {
		return pixelarray[-(Width * y) + x + cval].Attributes;

	}
}

DWORD unsafegetpix(int x, int y)
{
	
		return pixelarray[x + cval-Width * y].Attributes;

	
}





//unsafe method to set pix but 2 times faster
void unsafesetpix(int x, int y, DWORD col) {
		pixelarray[-(Width * y) + x + cval].Attributes = col;
}

void clearscreen() {






	for (int i = 0; i < Width * Height; i++)
	{
		
		pixelarray[i].Attributes = 0;

		pixelarray[i].Char.UnicodeChar = ' ';
	}


}
void drawframe() {


	COORD ScreenBufferCoord = { 0, 0 };
	SMALL_RECT ConsoleCoord = { 0, 0, Width, Height };

	WriteConsoleOutputA(*pHout, pixelarray, Dimval, ScreenBufferCoord, &ConsoleCoord);

 }


v2::Vector2 GetDim()
{
	return Dim;
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

			//revered x,y,and -x,-y
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
	void drawtriangle(triangle tri,DWORD col)
	{
		
		Vector2 carry= Vector2(0,0);
		if (tri[1].y> tri[2].y)
		{
			carry = tri[1];
			tri[1] = tri[2];
			tri[2] = carry;
		}
		if (tri[0].y > tri[2].y)
		{
			carry = tri[0];
			tri[0] = tri[2];
			tri[2] = carry;
		}
		if (tri[0].y > tri[1].y)
		{
			carry = tri[0];
			tri[0] = tri[1];
			tri[1] = carry;
		}
		int x3 =(tri[2].x);
		int y3 = (tri[2].y);
		bool firsttri = true;
		bool cm1=true;//canmove1
		int x = (tri[0].x);//
		int y = (tri[0].y);
		int x1 = (tri[1].x);//const
		int y1 =(tri[1].y);//const
	
		int dx = abs(x - x1);//dx for first one
		int sx = x <= x1 ? 1 : -1;//sign of x
		//no sign of y as we sorted   
		int dy = abs(y1 - y);
		
		int error = dx - dy;


		bool cm2 = true;
		int x12 = (tri[0].x);
		int y12 = (tri[0].y);
		int x2 = (tri[2].x);
		int y2 = (tri[2].y);
		int dx2 = abs(x12 - x2);
		int sx2 = x12 <= x2 ? 1 : -1;
		int dy2 = abs(y12 - y2);
	
		int error2 = dx2 - dy2;

		
		bool sef = false;//special end flag
		
		while (true) {
			if (cm1) {
				if (y == y1  &&x == x1&&sef) {

					return;
				}

				if (x == x1 && y == y1) {
					sef = true;
					cm1 = false;
				}  
				int e2 = error<<1;
				if (e2 >= -dy) {


					error -= dy;
					x += sx;
				}
				if (e2 <= dx) {

					error = error + dx;
					y += 1;
					cm1 = false;
				}
				if (x == x1 && y == y1) {
					sef = true;
					cm1 = false;
				}
			}


			if (cm2) {
				
				int e2 = error2*2;
				if (e2 >= -dy2) {


					error2 -= dy2;
					x12 += sx2;
				}
				if (e2 <= dx2) {

					error2 += dx2;
					y12 += 1;
					cm2 = false;

				}
			}
			if (!cm1 && !cm2 ) {
				if (x < x12) {
					for (int i = x; i <= x12; i++)
					{
						setpix(i, y12, col);
						
					}
				}
				else
				{

					for (int i = x12; i <= x; i++)
					{
						setpix(i, y12, col);
						
					}

				}

				if (sef&&firsttri)
				{
				x1 =(tri[2].x);//const
					y1 = (tri[2].y);//const

					dx = abs(x - x1);//dx for first one
					sx = x <= x1 ? 1 : -1;//sign of x
					//no sign of y as we sorted   
					dy = abs(y1 - y);

					 error = dx - dy;
					firsttri = false;

				}
				cm1 = true;
				cm2 = true;
			}
		}
		
	}

	void drawline(int x, int y, int x1, int y1, COLORREF pixelcol)
	{
		
		int dx = abs(x - x1);
		int sx = x <= x1 ? 1 : -1;
		int dy = abs(y1 - y);
		int sy = y <= y1 ? 1 : -1;
		
		int error = dx - dy;

		while(true) {
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
				drawbox(x0, ((y0 + y1) / 2),  2*thickness, (abs(y1 - y0)), pixelcol);
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


		const short dx = abs(sdx);
	const	short dy = abs(sdy);
		short sx = sdx >= 0 ? 1 : -1;
		int sy = sdy >= 0 ? 1 : -1;
		int x = x0;
		int y = y0;
		const short  E_diag = -2 * dx;
		const short E_square = 2 * dy;
		const short tdx = 2 * dx;
		const short threshold = dx - 2 * dy;
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
				tk +=  E_square;
			}

			error += E_square;
			y += sy;
			tk += tdx;

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
				tk += E_square;
			}

			error = error + E_square;
			y -= sy;
			tk +=tdx;

		}
	}


	void perpysub(int x0, int y0, int sdx, int sdy, int einit, int width, int winit,COLORREF pixelcol) {


		short dx = abs(sdx);
		short dy = abs(sdy);
		short sx = sdx >= 0 ? 1 :-1;
		short sy = sdy >= 0 ? 1 : -1;
		int x = x0;
		int y = y0;
		
		const short E_diag = -2 * dy;
			const short tdy = 2 * dy;
		const short E_square = 2 * dx;
		const short threshold = dy - 2 * dx;
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
				tk += E_square;
			}
			
			error = error + E_square;
				x +=sx;
				tk += tdy;
			
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
				tk += E_square;
			}

			error = error + E_square;
			x -=sx;
			tk += tdy;
			
		}
		
	}
		
	void drawthickcircle(short px, short py, short radius, COLORREF pixelval) {
		short y = 0;
		
		for (int i = - radius; i <=0; i++)
		{
			
			y=short(sqrt(radius * radius - i * i));
			for (short j = 0; j < y; j++)
			{
				//all j and i signs combinations
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
