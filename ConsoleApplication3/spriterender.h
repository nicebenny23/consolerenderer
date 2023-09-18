#include "dsprite.h"
#include "shader.h"
#include "dynamicarray.h"
#include "vector2.h"
#include "gameobject.h"
using namespace dynamicarray;
using namespace spritename;
using namespace gameobject;
#ifndef spriterender_H
#define spriterender_H
namespace spriterenderer {


	void drawtoscreen(gameobj sprit, scalemode scalemode);



	extern array<sprite*> spritelist;
	void render();
	void renderinit();



}
#endif // !spriterender
