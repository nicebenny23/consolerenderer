#include "vector2.h"
#include "sprite.h"
#ifndef shader_h
#define shader_h
using namespace sprite;	
struct fshader
{
	void (*shade) (spritec*);



	 fshader(void (*shadeinp) (spritec*));
	 

};


#endif // !
