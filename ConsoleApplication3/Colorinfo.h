#ifndef Colorc_HPP
#define Colorc_HPP
#include <stdint.h>


#include <Windows.h>
namespace Color {


const	DWORD colpallete[] = { 0x00000000,0x00040404,0x000B0B0B,0x00151515,0x00202020,0x002A2A2A,0x003A3A3A,0x004A4A4A,0x005B5B5B,0x006D6D6D,0x00808080,0x009C9C9C,0x00A7A7A7,0x00C2C2C2,0x00E9E9E9,0x00FFFFFF};

const	DWORD orgincolpallete[] = { 0x00000000,0x00111111,0x00222222,0x00333333,0x00444444,0x00555555,0x00666666,0x00777777,0x00888888,0x00999999,0x00AAAAAA,0x00BBBBBB,0x00CCCCCC,0x00DDDDDD,0x00EEEEEE,0x00FFFFFF };



	
DWORD col(int brightness);
DWORD invcol(int brightness);
	

	

}

#endif