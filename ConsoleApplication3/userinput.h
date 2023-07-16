#include "iostream"
#include <Windows.h>
#include "inpututil.h"
#ifndef userinput_HPP
#define userinput_HPP

namespace userinput {


	
	void getinput(HANDLE hin);
	extern inpututil::mouseinputstruct mousestate;
	extern DWORD newinputs;
	inpututil::inputkey& Getkey(char keyval);
	inpututil::inputkey &Getkeyc(char keyval);
	void resetkeys();
	void initiate();
	
	


	



}


#endif // !userinp
