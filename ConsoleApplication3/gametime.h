#include <chrono>
#include "dynamicarray.h"
using namespace dynamicarray;
using namespace std::chrono;
#ifndef timehpp
#define timehpp
steady_clock::time_point ptime;
float fps;
float dtime;
float gtime;
float tfps;
void inittime() {
	gtime = 0;
	tfps = 60;
	ptime = high_resolution_clock::now();
}

void calcfps() {
	
	auto a = high_resolution_clock::now();
	auto l = (a - ptime).count();
	auto g = duration_cast<nanoseconds>(  a-ptime).count();
	ptime = a;

	float dif = g /(1e9);
	fps = static_cast<float>(1e9) / g;
	dtime = g  / (1e9);
	gtime += dtime;
}

int currtimer =0;

struct  timer
{
	bool hitend;//on iff the timer has hit the max amount of time allocated
	bool fcount;//whether it goes by frame
	float currtime;//the current time on the timer
	timer();
	int timeid;
	bool on();
	void dec(float amt);
	void remove();
	bool running;//on iff the timer is running at the molment
	void start(float time);

};
array<timer*> timerlist = array<timer*>::array(0);


timer::timer() {
	fcount = false;
	hitend = true;
	running = false;

	timeid = currtimer;
	timerlist.append(this);
	currtimer++;


}

inline bool timer::on()
{
	//ifrunning will activate if being ran
	if (currtime ==0||!running)
	{
		return false;
	}
	return true;

}

inline void timer::dec(float amt)
{
	hitend = false;
	if (currtime > 0&&running)
	{


		if (fcount)
		{
			amt = 1;
		}
		currtime -= amt;
		if (currtime < 0)
		{
			running = false;
			hitend = true;
			currtime = 0;
		}
		
	}


}

inline void timer::remove()
{
	timerlist.deleteind(timeid);
	currtimer--;
}

inline void timer::start(float time)
{

	currtime = time;
	running = true;
}

int currwatch = 0;

struct  watch
{
	bool running;
	float currtime;
	watch(float time, bool srunning);
	int watchid;

	void inc(float amt);
	void remove();

	void start();


	
};
array<watch*> watchlist = array<watch*>::array(0);


watch::watch(float time,bool srunning) {


	currtime = time;
	watchid = currtimer;
	watchlist.append(this);
	currwatch++;
	running = srunning;

}


inline void watch::inc(float amt)
{
	if (running)
	{
		currtime += amt;

	}
	
}

inline void watch::remove()
{
	watchlist.deleteind(watchid);
	currwatch--;
}

 void watch::start()
{
	currtime = 0;
	running = true;
}


void calctimers() {


	for (int i = 0; i < watchlist.length; i++)
	{
		watchlist[i]->inc(dtime);
	}
	for (int i = 0; i < timerlist.length; i++)
	{
		timerlist[i]->dec(dtime );
	}
}
#endif // !timehpp
