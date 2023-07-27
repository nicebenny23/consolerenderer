#include "sprite.h"
#include <iostream>
#include "Renderer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "random.h"
#include <fcntl.h>
#include "Colorinfo.h"
using namespace sprite;
#pragma warning(disable: 4996)//will not compile without
//load sprite from file
spritefile::spritefile(const char* fpath)
{
    char* num;
    FILE* fp;
    struct stat fst;
    xdim = 0;
    ydim = 0;
    int len;
    fp = fopen(fpath, "r");
    if (fp == NULL)
    {
        std::exit(-66);
    }
    stat(fpath, &fst);
    len = fst.st_size;
    
    num = new char[len + 1];
    num[len] = '\0';
    fread(num, 1, len, fp);

    int firstcomma = 0;
    int pow = 1;
    bool firstreached = false;
    int pow2 = 1;
    int secondcomma = 0;
    for (int i = 0; i < len; i++)
    {
        if (firstreached)
        {
            if (num[i] == ';')
            {
                break;
            }
            //do this later than start so no divide
            pow2 *= 10;
        }
        else
        {
            if (num[i] == ';')
            {
               //swtop incrementing first cooma and pow
                firstreached = true;
            }
            else
            {

                //do this later so no divide
                pow *= 10;
                firstcomma++;
            }
        }
        //latwer so no divide
        secondcomma++;
        //oob
        if (num[i] != ';' && (int(num[i]) > 57 || int(num[i]) < 48))
        {
            std::exit(-66);
        }
    }

    firstreached = false;
    for (int i = 0; i < secondcomma; i++)
    {
        if (firstreached)
        {
            //shink valforst so i dont have to divide earlyer
            pow2 /= 10;
            
            ydim += (num[i] - 48) * pow2;
        }
        else
        {
            if (i >= firstcomma)
            {
                firstreached = true;
                continue;
            }
            pow /= 10;
            xdim += (num[i] - 48) * pow;
        }
    }

    

    bufdat = new short[xdim * ydim + 1];

    if (xdim * ydim != len - secondcomma - 1)
    {
        std::exit(-66);
    }
    //insert null char
    bufdat[xdim * ydim] = '\0';
    for (int i = 0; i < xdim * ydim; i++)
    {
        if (num[i + secondcomma + 1] >= 97 && num[i + secondcomma + 1] < 113)
        {
            bufdat[i] = num[i + secondcomma + 1] - 97;
        }
        else
        {
            std::exit(-22);
        }
    }
   
    fclose(fp);
    delete[] num;
}

//upscales and scales
short* sprite::scale(spritefile sprit, Vector2 scale,bool mode)
{
    int newx = ceil(sprit.xdim * abs(scale.x));
    int newy = ceil(sprit.ydim * abs(scale.y));
   double invscx = sprit.xdim / static_cast<float>(newx);
    double invscy = sprit.ydim / static_cast<float>(newy);
    int newtotal = newx * newy;
    short* newbuf = new short[(newtotal)];
    int xdm1 = sprit.xdim - 1;
    int ydm1 = sprit.ydim - 1;
    if (mode == true)
    {
        int s = 0;
        bool tst = false;
        for (int j = newy-1; j >= 0; j--)
        {
            double oy = j * invscy;
            int y = int(oy);
            int y1 = int(min((1 + y), ydm1));
            double dy = oy - y;
            double ox = 0;
            int xdm = sprit.xdim * y;
            int xdmp = sprit.xdim * y1;
            for (int i = 0; i < newx; i++)
            {

              
                int x =int(ox);
                int x1 = min((1 + x), xdm1);
               
             
               
                double dx =ox - x;
           
                double c = sprit.bufdat[x +xdm] * (1 - dy);
                double c1 = sprit.bufdat[x +xdmp] * (dy);
                double c2 = sprit.bufdat[x1 +xdm] * (1 - dy);
                double c3 = sprit.bufdat[x1 + xdmp] * (dy);
             
                newbuf[s] = short((1-dx)*(c + c1) + (c2 + c3)*dx);
             
                s++;
                ox += invscx;
            }
        }
        
    }
    else
    {
        int s = 0;
        for (int j = newy-1; j >=0; j--)
        {
            double oy = j * invscy;
            int y = min(int(oy), ydm1);
            double ox = 0;
           int yd = sprit.xdim * y;
            for (int i = 0; i < newx; i++)
            {
               

                int x = int(ox);
               
              short  c = sprit.bufdat[x+yd];

                newbuf[s] =c;
                s++;
                ox += invscx;
            }
        }
     
    }
    return newbuf;
  
}

// Interpolation function
float sprite::lerpa(float a, float b, float t)
{
    return a + t * (b - a);
}
sprite::spritec::spritec(const char* fpath, Vector2 pos) :file{ spritefile::spritefile(fpath) }
{


    this->pos = pos;

}
//false drawmode = pixelated else it it bilinier interpolated
void sprite::spritec::drawtoscreen(bool drawmode,short addcol)
{

    bool addingcol = false;
    if (addcol != 0)
    {
        addingcol = true;
    }
    Vector2 pos = this->pos;
   bool yflip = false;
    bool xflip = false;
    Vector2 scales = this->posscale;
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
    if (scales.y==0||scales.x==0)
    {
        return;
        //drawing here gives memory error and no need to draw here either
    }
    short* buf;
    if (scales.x==1&&scales.y==1)
    {
         buf = this->file.bufdat;
    }
    else
    {
       buf = scale(this->file, scales,drawmode);
    }
    short val = 0;
    int pxscle = ceil(this->file.xdim * scales.x);
    int pyscle = ceil(this->file.ydim * scales.y);

    //fliped sprites are drawn backwords

    int jsgn = (yflip) ? ( - 1) : 1;

    int xsgn = (xflip) ? (-1) : 1;
    int xstart = ((xflip) ? (pxscle - 1) : 0);
    int xend = ((!xflip) ? (pxscle - 1) : 0);
        int ydx = 0;
        int start = ((yflip) ? (pyscle - 1) : 0);
        int end = ((!yflip) ? (pyscle - 1) : 0);
       
        for (int j = start; j!= end; j+=jsgn)
        {
            

            int yp = (j + pos.y);
            int px = round(pos.x);

          
            for (int i = xstart; i != xend; i+=xsgn)
            {
                val = buf[i + ydx];
             
                if (val!= 0)
                {
                    if (addingcol){

                        val = min(max(1, val + addcol), 16);

                    }

                  
                //since pixels colors have diffrence of 16 and we alreadt checked for null pixels we can leftshift four times
                    
                    Render::setpix(px, yp, (val<<4)-16);
                }
                px++;
            }
            ydx += pxscle;
        }
        
    
    if (scales.x!= 1||scales.y!=1)
    {

        // we did nothing if scale was (1,1) due to optimizations so if we deleted it wed delete the whole buffer
        delete[] buf;
    }
  
}

short sprite::spritec::getpixfrompix(Vector2 pos)
{
    return 0;
}
