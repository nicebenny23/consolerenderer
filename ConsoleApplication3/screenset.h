#include <Windows.h>
#ifndef consoleset_HPP
#define ConsoleSet_HPP

namespace winutil
{
	DWORD orginmode;
	void setmode(HANDLE hin);
	void blockfull();
	void setbuffer(COORD size, COORD fonts, HANDLE hout);
	void setfont(COORD size, HANDLE hout);
	void setcursor(HANDLE hout);

	CONSOLE_SCREEN_BUFFER_INFOEX buf;






}
void winutil::setmode(HANDLE hin) {

	DWORD modes = ~0x0004 & ~0x0002;
	GetConsoleMode(hin, &orginmode);
	SetConsoleMode(hin, ENABLE_EXTENDED_FLAGS |
		(orginmode & ~ENABLE_QUICK_EDIT_MODE)&modes);
	 
}

void winutil::setcursor(HANDLE hout) {
	CONSOLE_CURSOR_INFO con;
	con.bVisible = false;

	SetConsoleCursorInfo(hout, &con);

}
void winutil::setbuffer(COORD size,COORD fonts,HANDLE hout) {
	buf.cbSize = sizeof(buf);
	GetConsoleScreenBufferInfoEx(hout, &buf);
	
	COORD charsize = COORD{ short(round(size.X / fonts.X)),short(round(size.Y / fonts.Y)) };
	

	


	buf.dwMaximumWindowSize = { 10000, 10000 };
	
buf.dwSize = charsize;
	buf.dwCursorPosition = { 0, 0 };
	buf.srWindow = { 0,0,short(charsize.X),short(charsize.Y )};
	SetConsoleScreenBufferInfoEx (hout, &buf);
}

void winutil::setfont(COORD size,HANDLE hout) {
	_CONSOLE_FONT_INFOEX font;
	font.FontFamily = 0;
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize = size;
	font.FontFamily = 0;
	font.FontWeight = 0;
	wcscpy_s(font.FaceName, L"Raster Fonts");
	SetCurrentConsoleFontEx(hout, FALSE, &font);

}
#endif