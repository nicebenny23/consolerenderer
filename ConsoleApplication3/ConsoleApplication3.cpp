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
using namespace Render;
using namespace Color;
using namespace std::chrono;

using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;
char* num;
int len;
int 	xdim = 8;
int 	ydim = 8;

int totxs;
int totys;
void setfilepix(const int x, const int y, char* dat,FILE* fp) {


	if (y <= ydim/2 && y >= -ydim/2 && x <=xdim/2 && x >= -xdim/2) {

		fseek(fp, 0, SEEK_SET);
		fwrite(dat, 1, xdim * ydim, fp);
	}
}
void setfilepix(const int x, const int y, const char* dat, FILE* fp) {


	fseek(fp, 0, SEEK_SET);
		fwrite(dat, 1, xdim * ydim, fp);
	
}
int indfrm(int x, int y) {


	return (round((200 + x ) / totxs))+xdim* (ydim - round((200 + y) / totys)-1) + len;
	
}

int main()
{
	
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
	

	FILE* fp;
	struct stat fst;

	 len= floor(floor(log10(xdim)) + 4 + floor(log10(ydim)));
	fp = fopen("fprintf.txt", "w");
	int tot = xdim * ydim;

	char* buf =new char[tot+1+len];
	for (int i = 0; i < tot+len; i++)
	{
		*(buf + i) = 97;
	}
	buf[tot+len] = 0;
	float t = 0;
	char l = '1';
	 userinput::initiate();
	 char sarr[6] = { '8',';' ,'8',';' };
	 for (int i = 0; i < len; i++)
	 {
		 buf[i] = sarr[i];
	 }
	 init();
	 totxs = floor (400 / (xdim ));
	 totys = floor( 400/(ydim));
	 
	 while (true)
	 {
		

		
		userinput::getinput(hIn);
		clearscreen();
		drawbox(0, 0, 400, 400, 160);
		for (int j = 0; j < ydim; j++) {
			for (int i = 0; i < xdim; i++)
			{
				char colnow = buf[ i + (ydim-j-1) * xdim+len];

			
				if (colnow!= 97)
				{
					drawbox(i * totxs - 200 + totxs / 2, j * totys - 200 + totys / 2, totxs - 2, totys - 2, (colnow - 97) << 4);
				}
				

			
			}
		}
		if (userinput::Getkey('g').pressed)
		{

			buf[indfrm(userinput::mousestate.pos.x, userinput::mousestate.pos.y)] = 100;
		
			setfilepix(0, 0, buf, fp);
			
		}
		 auto a = high_resolution_clock::now();
		

		
			
		
 auto b = high_resolution_clock::now();

			 auto g = duration_cast<nanoseconds>(b - a).count();
			 t += g / static_cast<float>(1'00'000);
	
			
			 drawframe();
			 userinput::resetkeys();

			
		 }
	 
	
	
	return 0;
	
}
