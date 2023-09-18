#include "vector2.h"
#include "dsprite.h"

#ifndef shader_h
#define shader_h

using namespace spritename;	
struct fshader
{
	void (*shade) (sprite*);



	 fshader(void (*shadeinp) (sprite*));
	 

};


#endif // !
