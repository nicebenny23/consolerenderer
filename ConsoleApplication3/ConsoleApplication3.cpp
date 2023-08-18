  #include <string>
#include "btree.h"
#include <iostream>

#include <chrono>
#include "Renderer.h"
#pragma warning(disable: 4996)
#include <Windows.h>
#include "screenset.h"
#include "Colorinfo.h"
#include "dynamicarray.h"
#include "polygon.h"
#include "sprite.h"
#include "userinput.h"
#include "random.h"
#include "safearray.h"
#include "camera.h"
#include "spriterender.h"
using namespace Render;
using namespace Color;
using namespace std::chrono;
using namespace saferarray;
using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;
const char* file = "fprintf.txt";
char* sp;

int xdim = 10;
int ydim = 10;
const char* namebuf = "10;10;";

int scx = 200;
int scy = 200;
int sc2y;
int sc2x;
int cnkx;
int cnky;
int extd = 0;
int ifp(Vector2 pnt) {



	pnt += Vector2(sc2x, -sc2y);
	pnt.x /= cnkx;
	pnt.y /= -cnky;
	
	if (pnt.x>=0&&pnt.x<xdim)
	{
		int ind = floor(pnt.x) + xdim * floor(abs(pnt.y));
		 if (pnt.y >= 0 && pnt.y < ydim)
		 {
			 return ind + extd;

		 }
	}
	
	
	
	return  -1;
}

void writebuftofile() {
	char* num;
	FILE* fp;
	struct stat fst;
	
	fp = fopen(file, "w");
	if (fp == NULL)
	{
		std::exit(-664);
	}
	stat(file, &fst);

	fwrite(sp, 1, static_cast<size_t>(xdim) * ydim+extd, fp);

}
int colr = 0;
int main()
{
	extd = floor(log10(xdim)) + floor(log10(ydim))+4;
	

	

	sc2x = scx / 2;
	sc2y = scy / 2;
	cnkx = scx / xdim;
	cnky = scy / ydim;


	 sp = new char[xdim*ydim+extd];
	 memcpy(sp, namebuf, extd);
	 memset(sp+extd, 97, static_cast<size_t>(xdim) * ydim);
	
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	static COORD screensize = { 800,800 };
	static COORD ftsize = { 2,2 };

	v2::Vector2 vbo = v2::Vector2(2, 2);

	SetConsoleTitleA("console render");    
	setmode(hIn);
	setcursor(hOut);
	setfont(ftsize, hOut);

	setbuffer(screensize, ftsize, hOut);
                       

	createscreen(screensize.X, screensize.Y, ftsize, &hOut);
	
	float t = 0;
	
	 userinput::initiate();
	 int flashtime=0;
	 init();
	 int shots = 0;
	 Vector2 shotpos = zerov;
	 bool shot = false;
	 camera::init();
	 while (true)
	 {
		
	
		userinput::getinput(hIn);
		clearscreen();
		//drawbox(0, -100, 400, 200, 160);
		 auto a = high_resolution_clock::now();
		 if (userinput::Getkey('d').pressed)
		 {
			 if (colr < 15) {
				 colr++;
			 }
		 }
		 if (userinput::Getkey('a').pressed)
		 {
			 if (colr >0) {
				 colr--;
			 }
		 }
		 if (userinput::Getkey('x').held)
		 {
			 int cind = ifp(userinput::mousestate.pos);
			 if (cind!=-1)
			 {
				 sp[cind] = 97+colr;
			
			 }
			 

		}
		 if (userinput::Getkey('c').held)
		 {
			 int cind = ifp(userinput::mousestate.pos);
			 if (cind != -1)
			 {
				colr= sp[ifp(userinput::mousestate.pos)]- 97 ;

			 }


		 }

		 if (userinput::Getkey('w').pressed)
		 {
			 writebuftofile();
		 }
		 int ind = extd;
		 for (int j = ydim-1; j >=0 ; j--)
		 {
		 for (int i = 0; i < xdim; i++)
		 {
			 if (sp[ind] == 97) {

				 drawbox(i * cnkx - sc2x + cnkx / 2 + cnkx / 4, j * cnky - sc2y + cnky / 2+ cnky / 4, cnkx / 2, cnky / 2, 80);
				 drawbox(i * cnkx - sc2x + cnkx / 2-cnkx/4, j * cnky - sc2y + cnky / 2- cnky / 4, cnkx/2, cnky/2,80);
				 drawbox(i * cnkx - sc2x + cnkx / 2, j * cnky - sc2y + cnky / 2, cnkx, cnky, 160);
			}
				 drawbox(i * cnkx - sc2x+cnkx/2, j * cnky - sc2y+ cnky / 2, cnkx, cnky, (sp[ind]-97)<<4);
				 ind++;
			 }
			 
		 }
		 drawbox(0, 0, 400, 400, 0);
		 drawframe();
			 userinput::resetkeys();
			 auto g= 0;
			 do
			 { 
				 

				 auto b = high_resolution_clock::now();
				 g = duration_cast<nanoseconds>(b - a).count();
			 } while (g < 100000);
			 


			 t += g / static_cast<float>(1'00'000000);
		 }

	 return 0;
	
}
