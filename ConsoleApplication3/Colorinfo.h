#ifndef Colorc_HPP
#define Colorc_HPP
#include <stdint.h>


#include <Windows.h>
namespace Color {




#define Clay BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define White BACKGROUND_INTENSITY|BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE


#define Grey 0x0080



#define Purple 0x0050
#define Lightpurple 0x0050|BACKGROUND_INTENSITY

#define hv 0x0800|0x1000|COMMON_LVB_UNDERSCORE|0x0400
#define tst 0x0300
	
#define Green 0x0020
#define Lime 0x0020|BACKGROUND_INTENSITY

#define Yellow 0x0060
#define Tan 0x0060|BACKGROUND_INTENSITY

#define Blue 0x0010
#define Brightblue 0x0010|BACKGROUND_INTENSITY



#define Lightblue 0x0030
#define Cyan 0x0030|BACKGROUND_INTENSITY


#define Red 0x0040
#define Pink 0x0040|BACKGROUND_INTENSITY

	
#define BLACK 0
	const COLORREF PALETTE_GREYSCALE[16] =
	{
		BLACK,White,Blue,Brightblue,Green, Lime,Lightblue,Cyan,Red,Pink,Purple,Lightpurple,Clay,Yellow,Tan,White };
	
	class Pallete
	{
	public:
		Pallete();
		uint8_t brighten(uint8_t color);
		


	private:

	
	};
	
	

	

}

#endif