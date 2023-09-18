#include <Windows.h>
#ifndef consoleset_HPP
#define ConsoleSet_HPP
#include "Colorinfo.h"
#pragma once
namespace winutil
{
	static DWORD orginmode;

	void setmode(HANDLE hin);
	void blockfull();
	void setbuffer(COORD size, COORD fonts);
	void setfont(COORD size);
	void setcursor();
	void settitle();
	void createbuf();
	 
	 HANDLE* getouthand();





}

#endif