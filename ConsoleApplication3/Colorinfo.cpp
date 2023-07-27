#include "Colorinfo.h"



namespace Color {



	DWORD Color::col(int brightness) {



		if (brightness < 0) {
			return (0);
		}
		if (brightness>15)
		{
			return (240);
		}
		return (brightness<<4);
	}

	inline DWORD invcol(int brightness)
	{
		return 240 - col(brightness);
	}
	
}

