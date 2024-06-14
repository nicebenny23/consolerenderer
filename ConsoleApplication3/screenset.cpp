#include "screenset.h"
#include <Windows.h>
#include <corecrt_math.h>

HANDLE buf2;
HANDLE hin;
//enables fullscreen
void fullscreen() {
	
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

//disables varios console fetures to make ity more like a renderer
void winutil::setmode(HANDLE hin) {

	DWORD modes = ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_QUICK_EDIT_MODE) | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	GetConsoleMode(hin, &orginmode);
	SetConsoleMode(hin, modes);

}
//makes cursor work more like in a game 
void winutil::setcursor() {
	CONSOLE_CURSOR_INFO con;

	GetConsoleCursorInfo(buf2, &con);
	con.bVisible = false;

	SetConsoleCursorInfo(buf2, &con);
	ShowCursor(false);
}
//gets the ouptut handle
 HANDLE* winutil::getouthand()
{


	return &buf2;
}
 void winutil::setbuffer(COORD size, COORD fonts) {
	 hin = GetStdHandle(STD_INPUT_HANDLE);

	COORD charsize = COORD{ short(round(size.X / fonts.X)),short(round(size.Y / fonts.Y)) };
	buf2 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,		  
		FILE_SHARE_READ | FILE_SHARE_WRITE,	 NULL,CONSOLE_TEXTMODE_BUFFER,NULL);								 



	CONSOLE_SCREEN_BUFFER_INFOEX buf = CONSOLE_SCREEN_BUFFER_INFOEX();
	buf.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	for (int i = 0; i < 16; i++)
	{
		buf.ColorTable[i] = Color::colpallete[i];

	}


	//bgr
	//buf.ColorTable[1] = 0x0000FF00;





	buf.dwMaximumWindowSize = { 10000, 10000 };

	buf.dwSize = charsize;
	buf.wAttributes = 0;
	buf.wPopupAttributes = 0;

	buf.bFullscreenSupported = false;
	buf.dwCursorPosition = { 0, 0 };
	buf.srWindow = { 0,0,short(charsize.X),short(charsize.Y) };

	SetConsoleScreenBufferInfoEx(buf2, &buf);
	SetConsoleActiveScreenBuffer(buf2);
	
	setfont(fonts);
	setmode(hin);
	setcursor();
	SetConsoleTitleA("console render");
	//fullscreen();
 }
 
 //sets used font
 void winutil::setfont(COORD size) {
	_CONSOLE_FONT_INFOEX font;
	GetCurrentConsoleFontEx(buf2, false, &font);

	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize = size;
	font.FontFamily = 0;
	font.FontWeight = 0;
	wcscpy_s(font.FaceName, L"Raster Fonts");

	SetCurrentConsoleFontEx(buf2, FALSE, &font);
}

 void getsize() {


 }