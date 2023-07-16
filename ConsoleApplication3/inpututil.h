#ifndef userinpututil_HPP
#define userinpututil_HPP
#include "vector2.h"

namespace inpututil {
	struct mouseinputstruct {
		v2::Vector2 pos;
		



	};
	struct inputkey
	{
		void onrelesed();
		void onpressed();
		void resetkeyval();
		bool held;
		bool letgo;
		bool pressed;
	};

	inline void inputkey::onrelesed() {

		letgo= true;
		held = false;
	}

	inline void inputkey::onpressed() {
		
	
			held = true;
			pressed = true;
		

	}

	inline void inputkey::resetkeyval() {

		pressed = false;
	letgo= false;

	}
}
#endif