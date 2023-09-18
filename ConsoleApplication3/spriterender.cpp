#include "spriterender.h"
#include "Renderer.h"
#include "dsprite.h"
#include "camera.h"
#include "shader.h"
#include "oalgorithm.h"
#include "random.h"
#include "safearray.h"
#include "gameobject.h"
using namespace spritename;
using namespace gameobject;
using namespace spriterenderer;
array<sprite*> spriterenderer::spritelist;



float val = 0;
void spriterenderer::drawtoscreen(gameobj sprit,scalemode drawmode)
{
   
   
    Vector2 pos = sprit.pos-camera::camerapos;
    pos *= camera::cscale;
    bool yflip = false;
    bool xflip = false;
    Vector2 scales = sprit.scale*camera::cscale;
    Vector2 abscale= scales;
   
        if (scales.x < 0)
        {
            abscale.x = abs(scales.x);
            
        }
        if (scales.y < 0)
        {
            abscale.y = abs(scales.y);
             
        }
    
   
    int ydd2 = floor(sprit.sprit.ydim * abscale.y / 2);
    int xdd2 = floor(sprit.sprit.xdim * abscale.x / 2);
    int pxscle = ceil(sprit.sprit.xdim * abscale.x);
    int pxlscle = -xdd2;
    int pxrscle = xdd2;
    int pyuscle = ydd2;
    int pydscle = -ydd2;

    int sxd2 = ceil(Render::GetDim().x / 2) - 1;
    int syd2 = ceil(Render::GetDim().y / 2) - 1;
    int pyscle = (sprit.sprit.ydim * abscale.y);


  
 
    if (pyuscle + pos.y <= -syd2 || pydscle + pos.y >= syd2)
    {
        return;
    }
    if (pxrscle + pos.x <= -sxd2 || pxlscle + pos.x >= sxd2)
    {
        return;
    }
    //sprite modification shader which can be a fragment shader that can do more goes here this dissalows movment but that stuff goes below



    if (pydscle + pos.y <= -syd2)
    {
        pydscle = -syd2 - pos.y;
    }
   
    if (pyuscle + pos.y >= syd2)
    {
        pyuscle = syd2 - pos.y;
    }

    if (pxlscle + pos.x <= -sxd2)
    {
        pxlscle = -sxd2 - pos.x;
    }
  
    if (pxrscle + pos.x >= sxd2)
    {
        pxrscle = sxd2 - pos.x;
    }

    if (scales.y == 0 || scales.x == 0)
    {
        return;
        //drawing here gives memory error and no need to draw here either
    }

  



  
       
    sprite buf;
    
    if (drawmode == norm)
    {
        sprite d = sprit.sprit;
 
        buf = scale(sprit.sprit, scales, drawmode);
     
        int m = 2;
    }
    else
    {

       
        buf = scale(sprit.sprit, abscale, drawmode);
        buf *= camera::cscale;
       
    }
  
    
    char val = 0;
  
    //fliped sprites are drawn backyords

  

  

    
    int yp = pydscle + pos.y;

    for (int j = pydscle; j < pyuscle; j++)
    {

        //   Render::drawframe();
        int px = pxlscle + pos.x;

        int ydx = (pxscle) * ((pyscle - (j + ydd2)-1));

        for (int i = pxlscle; i != pxrscle; i++)
        {
            val = buf.bufdat[i + ydx + xdd2];

            if (val != 0)
            {


                //since pixels colors have diffrence of 16 and we alreadt checked for null pixels we can leftshift four times
                //for pixel position shader will need to replace unsafe pixset with safe pix set
                //also alpha values could set an extra atribbute that would be used to divide and let other colors throgh
                //will make most of this as genral to also alow for things like lights
                //will use ascii field of charinfo to store it
                Render::unsafesetpix(px, yp, (val << 4) - 16);

            }
            px ++;

        }
        yp++;
    }
    delete[] buf.bufdat;
   
}

void spriterenderer::render()
{
    saferarray::safearray<sprite> arr = saferarray::safearray<sprite>(spritelist.length);
    for (int i = 0; i < spritelist.length; i++)
    {
        arr[i] = *spritelist[i];

    }
  for (int i = spritelist.length-1; i >= 0; i--)
    {
     
    }

}

void spriterenderer::renderinit()
{

    spritelist = array<sprite*>(2);
}
