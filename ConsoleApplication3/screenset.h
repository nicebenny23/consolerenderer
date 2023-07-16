#include <Windows.h>
#ifndef consoleset_HPP
#define ConsoleSet_HPP
#include "Colorinfo.h"
namespace winutil
{
	DWORD orginmode;

	void setmode(HANDLE hin);
	void blockfull();
	void setbuffer(COORD size, COORD fonts, HANDLE hout);
	void setfont(COORD size, HANDLE hout);
	void setcursor(HANDLE hout);
	void settitle();
	CONSOLE_SCREEN_BUFFER_INFOEX buf;






}
void winutil::setmode(HANDLE hin) {

	DWORD modes = ~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|ENABLE_QUICK_EDIT_MODE) | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS  ;
	GetConsoleMode(hin, &orginmode);
	SetConsoleMode(hin, modes);
	 
}

void winutil::setcursor(HANDLE hout) {
	CONSOLE_CURSOR_INFO con;

	GetConsoleCursorInfo(hout, & con);
	con.bVisible = false;
	
	SetConsoleCursorInfo(hout, &con);
	ShowCursor(false);
}
void winutil::setbuffer(COORD size,COORD fonts,HANDLE hout) {
	buf.cbSize = sizeof(buf);
	GetConsoleScreenBufferInfoEx(hout, &buf);
	for (int i = 0; i < 16; i++)
	{
		buf.ColorTable[i]=Color::colpallete[i];

	}

	//bgr
	//buf.ColorTable[1] = 0x0000FF00;
	COORD charsize = COORD{ short(round(size.X / fonts.X)),short(round(size.Y / fonts.Y)) };
	

	


	buf.dwMaximumWindowSize = { 10000, 10000 };
	
buf.dwSize = charsize;
	buf.dwCursorPosition = { 0, 0 };
	buf.srWindow = { 0,0,short(charsize.X),short(charsize.Y )};
	SetConsoleScreenBufferInfoEx (hout, &buf);
}

void winutil::setfont(COORD size,HANDLE hout) {
	_CONSOLE_FONT_INFOEX font;
	
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize = size;
	font.FontFamily = 0;
	font.FontWeight = 0;
	wcscpy_s(font.FaceName, L"Raster Fonts");
	
	SetCurrentConsoleFontEx(hout, FALSE, &font);
	
}
#endif