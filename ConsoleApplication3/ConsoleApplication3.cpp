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

char* num;


sprite::spritec gp = sprite::spritec("bullet.txt", zerov);

sprite::spritec gd = sprite::spritec("fprintf.txt", zerov);


int currspawnbird;
int bl = 0;

struct bird
{
	void movebirdt();
	int birdin;
	array<Vector2> locations;
	float speed;
	bool alive;
	spritec spir;
	
	Vector2 cpos;
	float pdis;
	Vector2 wpos;
	int pct;
	int timeleft;
	bird();
	bird(int basespeed);
};
struct wave
{
	int amount;
	int basespeed;
	int length;
	int bt;


};
wave amount[] = { wave{4,1,3,34},wave{3,4,6,6},wave{1,0,10,1 } };
int wavm = sizeof(amount)/sizeof(amount[0]);
void bird::movebirdt() {
	
	if (distance(cpos,wpos)<=speed)
	{
		pct++;
		
		wpos = Vector2((random() - .5)*400,random()*300-100);
		spir.posscale.x = 4;
		if (wpos.x<spir.pos.x)
		{
			spir.posscale.x = -4;
		}
		pdis = distance(cpos, wpos);
	}
	else {

		cpos += normal((wpos - cpos))*speed;

	}
	spir.pos = cpos;


}
int currwav;
bird::bird() {
	birdin = currspawnbird;
	
	spir = sprite::spritec("fprintf.txt", zerov);
	spir.posscale = Vector2(4,4);
	cpos = zerov;
	timeleft = 100;
	speed = 0;
	pct = 0;
	alive = true;
	pdis = distance(cpos, wpos);

}
bird::bird(int basespeed) {
	birdin = currspawnbird;
	
	spir = sprite::spritec("fprintf.txt", zerov);
	spir.posscale = Vector2(-4,4);
	cpos = zerov;
	timeleft = 100;
	speed = basespeed;
	pct = 0;
	alive = true; 
	pdis = distance(cpos, wpos);
	
}
array<bird> birdlist=array<bird>::array();
int main()
{
	currwav = 0;
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
		
		 // camera::camerapos = Vector2(3, 4 * t);
		 camera::cscale = Vector2(1, 1);
		userinput::getinput(hIn);
		clearscreen();
		//drawbox(0, -100, 400, 200, 160);
		 auto a = high_resolution_clock::now();
		 drawbox(0, -150, 400, 100, 96);
	
	//	pipe.render();
		 
		  sprite::spritec spid = sprite::spritec("dog.txt", zerov);
		  spriterenderer::drawtoscreen(&spid, wrap);
		 if (birdlist.length ==0)
		 {
			 if (currwav<wavm)
			 {
				 for (int i = 0; i < amount[currwav].amount; i++)
				 {
					 birdlist.append(bird(amount[currwav].basespeed));
				 }
				 shots = amount[currwav].bt;
				 bl = amount[currwav].amount;
				 currwav++;
				
			 }

		 }
		 if (flashtime>0)
		 {
			 flashtime--;

			 if (flashtime>9)
			 {
				 drawbox(0, 0, 400, 400, 240);

			 }
			 else
			 {
				 gp.pos = shotpos;
				 gp.posscale = unitv * flashtime * flashtime / 12;
				 spriterenderer::drawtoscreen(&gp, norm);

			 }
			
		 }
		 if (userinput::Getkey('x').pressed) {


			 if (flashtime < 1)
			 {
				 flashtime = 12;
				 shots--;
				 shotpos = userinput::mousestate.pos;
				 shot = true;
			 }

			
			
		 }

		 for (int i = 0; i < birdlist.length; i++)
		 {
			 
			
			
				
				
				
				  if (birdlist.getelem(i).spir.inbounds(userinput::mousestate.pos)&& birdlist.at(i).alive==true&&shot)
				 {

					 birdlist.at(i).alive = false;
				
					 bl--;
				 }
			
			 if (birdlist[i].alive)
			 {
				 birdlist[i].movebirdt();
				 
			 }
			 else {

				 if (birdlist[i].cpos.y< -100) {
					 birdlist.deleteind(i);
					
					 continue;
				 }
				 else
				 {
					 birdlist[i].spir.pos -= (Vector2(0, 2));
					 birdlist[i].cpos -= (Vector2(0, 2));
				 }
			 }
			 spriterenderer::drawtoscreen(&birdlist[i].spir,norm);
			

		

		 }
		 shot = false;
		 if (shots <= 0 &&bl !=0)
		 {
			 return 1;
		 }
		
		 gp.pos = Vector2(160, -200);
		 gd.pos = Vector2(-150, -150);
		 gd.posscale = Vector2(bl, 1);
		 gp.posscale = Vector2(1, 1);
		 spriterenderer::drawtoscreen(&gd, wrap);
		 for (int i = 0; i < shots; i++)
		 {
		
			 gp.pos += Vector2(0, 6);
			
			
			 spriterenderer::drawtoscreen(&gp, norm);
		 }
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
