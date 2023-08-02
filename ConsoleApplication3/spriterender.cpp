#include "spriterender.h"
#include "Renderer.h"
#include "sprite.h"
#include "shader.h"

using namespace sprite;




void spriterenderer::drawtoscreen(spritec* sprit,bool drawmode, short addcol)
{

    bool addingcol = false;
    if (addcol != 0)
    {
        addingcol = true;
    }
    Vector2 pos = sprit->pos;
    bool yflip = false;
    bool xflip = false;
    Vector2 scales = sprit->posscale;

    if (scales.x < 0 || scales.y < 0) {

        if (scales.x < 0)
        {
            scales.x = abs(scales.x);
            xflip = true;
        }
        if (scales.y < 0)
        {
            scales.y = abs(scales.y);
            yflip = true;

        }
    }
    int ydd2 = floor(sprit->file.ydim * scales.y / 2);
    int xdd2 = floor(sprit->file.xdim * scales.x / 2);
    int pxscle = ceil(sprit->file.xdim * scales.x);
    int pxlscle = -xdd2;
    int pxrscle = xdd2;


    int sxd2 = ceil(Render::GetDim().x / 2) - 1;
    int syd2 = ceil(Render::GetDim().y / 2) - 1;
    int pyscle = (sprit->file.ydim * scales.y);


    int pyuscle = ydd2;



    int pydscle = -ydd2;
    if (pydscle + pos.y <= -syd2)
    {
        pydscle = -syd2 - pos.y;
    }
    if (pyuscle + pos.y <= -syd2 || pydscle + pos.y >= syd2)
    {
        return;
    }
    if (pyuscle + pos.y >= syd2)
    {
        pyuscle = syd2 - pos.y;
    }

    if (pxlscle + pos.x <= -sxd2)
    {
        pxlscle = -sxd2 - pos.x;
    }
    if (pxrscle + pos.x <= -sxd2 || pxlscle + pos.x >= sxd2)
    {
        return;
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

    short* buf;

    {

        sprit->pos = Vector2(0, 0);

        spritec dd = spritec("line.txt", zerov);

        dd.posscale = Vector2(10, 10);

       
        buf = applytex(*sprit, dd, true, false);


        buf = scale(buf, scales, drawmode, sprit->file.xdim, sprit->file.ydim);
    }
    short val = 0;
  
    //fliped sprites are drawn backyords



    int jsgn = (yflip) ? (-1) : 1;

    int xsgn = (xflip) ? (-1) : 1;
    int xstart = ((!xflip) ? (pxlscle) : pxrscle);
    int c = 0;
    if (xflip)
    {
        c = pxlscle;
        pxlscle = -pxrscle;
        pxrscle = -c;
    }
    if (yflip)
    {
        c = pyuscle;
        pyuscle = -pydscle;
        pydscle = -c;
    }
    int ystart = ((yflip) ? (pyuscle - 1) : pydscle);


    int yp = pos.y + ystart;
    for (int j = pydscle; j != pyuscle; j++)
    {


        //   Render::drawframe();
        int px = xstart + pos.x;
        int ydx = (pxscle) * (j + ydd2);

        for (int i = pxlscle; i != pxrscle; i++)
        {
            val = buf[i + ydx + xdd2];

            if (val != 0 && Render::unsafegetpix(px, yp) == 0)
            {
                if (addingcol) {


                    val += addcol;
                    if (val > 16)
                    {
                        val = 16;
                    }
                    else if (val < 1)
                    {
                        val = 1;
                    }

                }


                //since pixels colors have diffrence of 16 and we alreadt checked for null pixels we can leftshift four times

                Render::unsafesetpix(px, yp, (val << 4) - 16);

            }
            px += xsgn;

        }

        yp += jsgn;
    }

    delete[] buf;

}
