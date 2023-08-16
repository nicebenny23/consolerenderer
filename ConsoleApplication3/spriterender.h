#include "sprite.h"
#include "shader.h"
#include "dynamicarray.h"
#include "vector2.h"

using namespace dynamicarray;
using namespace sprite;
#ifndef spriterender_H
#define spriterender_H
namespace spriterenderer {


	void drawtoscreen(spritec* sprit, scalemode scalemode);



	extern array<spritec*> spritelist;
	void render();
	void renderinit();



}
#endif // !spriterender
