     #include <string>
#include "btree.h"
#include <iostream>

#include <chrono>
#include "Renderer.h"
#pragma warning(disable: 4996)
#include <Windows.h>
#include "screenset.h"
#include "gametime.h"
#include "Colorinfo.h"
#include "dynamicarray.h"
#include "polygon.h"
#include "dsprite.h"
#include "userinput.h"
#include "random.h"
#include "safearray.h"
#include "camera.h"
#include "spriterender.h"
#include "gameobject.h"
using namespace spritename;
using namespace Render;
using namespace Color;
using namespace std::chrono;
using namespace saferarray;
using namespace dynamicarray;
using namespace winutil;
using namespace pgon;
using namespace v2;
using namespace gameobject;
char* num;




int currspawnbird;
int bl = 0;
;


class tree : public component {

	virtual void update() override {
		holder->scale = Vector2(10, 10);
		holder->pos = Vector2(100, -50);

		spriterenderer::drawtoscreen(*holder, norm);

		holder->pos = Vector2(0, -50);

		spriterenderer::drawtoscreen(*holder, norm);
		holder->pos = Vector2(100, -50);

		spriterenderer::drawtoscreen(*holder, norm);

	}


};
struct bird1 : public component {
	int* birdcounter;
	int birdin;
	array<Vector2> locations;
	float speed;
	bool alive;
	
	virtual void ondestroy() override {
		(*birdcounter)--;
	}
	;
	Vector2 cpos;
	float pdis;
	Vector2 wpos;
	int pct;
	int timeleft;
	bird1() {

	}
	bird1(int basespeed,int* counterloc) {

		birdin = currspawnbird;
		birdcounter = counterloc;

		(*counterloc)++;
		cpos = zerov;

		speed = basespeed;
		pct = 0;
		alive = true;
		pdis = distance(cpos, wpos);

	}
	virtual void start() {


		holder->scale = Vector2(-4, 4);
	}


	virtual void update() override {
		



		if (holder->sprit.inbounds(userinput::mousestate.pos) && this->alive == true && userinput::Getkey('x').held)
		{

			alive = false;

			bl--;
		}

		if (alive && *birdcounter> 0)
		{
			if (distance(cpos, wpos) <= speed)
			{
				pct++;

				wpos = Vector2((random() - .5) * 400, random() * 300 - 100);
				holder->scale.x = 4;

				if (wpos.x < holder->pos.x)
				{
					holder->scale.x = -4;
					
				}
				pdis = distance(cpos, wpos);
			}
			else {

				cpos += normal((wpos - cpos)) * speed;
				
			}
			holder->pos = cpos;
			holder->sprit.pos = cpos;
		
		}
		else {

			if (holder->pos.y < -100) {
				destroy(holder);

				
			}
			else
			{
				holder->pos -= (Vector2(0, 2));
;

			}
		}

		spriterenderer::drawtoscreen(*holder, norm);
				}


};

struct bird
{
	void movebirdt();
	int birdin;
	array<Vector2> locations;
	float speed;
	bool alive;
	gameobj* spir;
	
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

wave amount[] = { wave{2,2,3,10},wave{3,4,6,6},wave{1,4,10,1 } };
int wavm = sizeof(amount)/sizeof(amount[0]);
void bird::movebirdt() {
	
	if (distance(cpos,wpos)<=speed)
	{
		pct++;
		
		wpos = Vector2((random() - .5)*400,random()*300-100);
		spir->scale.x = 4;
		
		if (wpos.x<spir->pos.x)
		{
			spir->scale.x = -4;
			
		}
		pdis = distance(cpos, wpos);
	}
	else {

		cpos += normal((wpos - cpos))*speed;

	}
	spir->pos = cpos;
	spir->sprit.pos = cpos;

}
int currwav;
bird::bird()  {
	
}
bird::bird(int basespeed) {
	birdin = currspawnbird;
	
 spir = new gameobj(zerov,unitv,"fprintf.txt","ee");
	spir->scale = Vector2(-4,4);
	
	cpos = zerov;
	
	speed = basespeed;
	pct = 0;
	alive = true; 
	pdis = distance(cpos, wpos);

	int s = 3;

}


const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
static COORD screensize = { 800,800 };
static COORD ftsize = { 2,2 };


void mainsetup() {

	inittime();
	randominit();
	setbuffer(screensize, ftsize);
	createscreen(screensize.X, screensize.Y, ftsize);
	initobjs();
	userinput::initiate();
	
	camera::init();
}

int birdamount;
int main()
{
	birdamount = 0;
	mainsetup();

	gameobj gp = gameobj(zerov, unitv, "bullet.txt", "hee");
	gameinit(zerov, unitv, "tree.txt", "eye").obj()->addcomponent<tree>();
	
	 gameobjref gd = gameinit(zerov, unitv, "fprintf.txt", "eey");
	
	timer flashtime = timer::timer();
	
	

	currwav = 0;

	 
	  
	 
  	 int shots = 0;
	 Vector2 shotpos = zerov;
	 bool shot = false;
	 int gl = 0;
	 while (true)
	 {
		 drawbox(2, 2, 400, 400,32);
		
		 camera::camerapos = Vector2(0, 0);
		 camera::cscale = Vector2(1, 1);
		userinput::getinput(hIn);
		clearscreen();
		gl++;
	
		
		
		
	
		runupdateloop();
		deleteobjs();
		

		 drawbox(0, -150, 400, 100, 96);
	
	//	pipe.render();
		 

		 if ( birdamount==0)
		 {
			 if (currwav<wavm)
			 {
				 for (int i = 0; i < amount[currwav].amount; i++)
				 {
					 gameinit(zerov, unitv, "fprintf.txt", "33").obj()->addcomponent<bird1>(amount[currwav].basespeed, &birdamount);
		
				 }
				
				 shots = amount[currwav].bt;
				 bl = amount[currwav].amount;
				 currwav++;
		
				
			 }
		
		 }
		

		 if (flashtime.on())
		 {
			

			
				 drawbox(0, 0, 400, 400, 240);

			 
			
		 gp.pos = shotpos;
				
				 gp.scale = unitv * flashtime.currtime * flashtime.currtime ;
				
				 spriterenderer::drawtoscreen(gp, norm);
				 
			 
			
		 }
		 if (userinput::Getkey('x').pressed) {


			 if (flashtime.on() == false)
			 {
				 flashtime.start(.2);
				 
				 shots--;
				 shotpos = userinput::mousestate.pos;
				 shot = true;
			 }

			
			
		 }
		
	

		 shot = false;
		 if (shots <= 0 &&bl !=0)
		 {
			 return 1;
		 }
		
	
		 gp.pos = Vector2(160, -200);
		
		 gd.obj()->pos = Vector2(-150, -150);
		 
		 gd.obj()->scale = Vector2(bl, 1);
		 

		
		gp.scale = Vector2(2, 2);
		 spriterenderer::drawtoscreen(*gd.obj(), wrap);
		 for (int i = 0; i < shots; i++)
		 {
		
		 
		 gp.pos += Vector2(0, 9);

			//
			 spriterenderer::drawtoscreen(gp,norm);
		 }
		
		 drawframe();
			
			 
			 calcfps();
			 calctimers();
			float l = fps;
			userinput::resetkeys();
		

		 }
	 
	
	
	return 0;
	
}
