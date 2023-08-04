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
#include "spriterender.h"
using namespace Render;
using namespace Color;
using namespace std::chrono;

using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;

char* num;
sprite::spritec sp = sprite::spritec("fprintf.txt",zerov);
sprite::spritec gp = sprite::spritec("fprintf.txt", zerov);
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
	
	float t = 0;
	
	 userinput::initiate();
	
	 init();

	 while (true)
	 {
		
		 
		
		userinput::getinput(hIn);
		clearscreen();
	
		 auto a = high_resolution_clock::now();
		 sp.pos = Vector2(abs(int(2*t)%400-200)*2-200,200-round(t/100)*50);
		 sp.posscale = Vector2(10, 10);
	//	pipe.render();

		 spriterenderer::drawtoscreen(&sp, false);
			
	
			
			 drawframe();
			 userinput::resetkeys();
			 auto g= 0;
			 do
			 {
				 auto b = high_resolution_clock::now();
				 g = duration_cast<nanoseconds>(b - a).count();
			 } while (g < 1000000);
			 



			 t += g / static_cast<float>(1'00'000000);
		 }
	 
	
	
	return 0;
	
}
