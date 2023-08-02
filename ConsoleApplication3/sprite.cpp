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
short* sprite::scale(spritefile sprit, Vector2 scale, bool mode)
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
        for (int j = newy - 1; j >= 0; j--)
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


                int x = int(ox);
                int x1 = min((1 + x), xdm1);



                double dx = ox - x;

                double c = sprit.bufdat[x + xdm] * (1 - dy);
                double c1 = sprit.bufdat[x + xdmp] * (dy);
                double c2 = sprit.bufdat[x1 + xdm] * (1 - dy);
                double c3 = sprit.bufdat[x1 + xdmp] * (dy);




                newbuf[s] = short((1 - dx) * (c + c1) + (c2 + c3) * dx);

                s++;
                ox += invscx;
            }
        }

    }
    else
    {
        int ind = 0;
        for (int j = newy - 1; j >= 0; j--)
        {
            double oy = j * invscy;
            int y = min(int(oy), ydm1);
            double ox = 0;
            int yd = sprit.xdim * y;
            for (int i = 0; i < newx; i++)
            {


                int x = int(ox);

                short  c = sprit.bufdat[x + yd];

                newbuf[ind] = c;
                ind++;
                ox += invscx;
            }
        }

    }
    return newbuf;

}

short* sprite::scale(short* sprit, Vector2 scale, bool mode, int xdim, int ydim)
{

    int newx = ceil(xdim * abs(scale.x));
    int newy = ceil(ydim * abs(scale.y));
    double invscx = xdim / static_cast<float>(newx);
    double invscy = ydim / static_cast<float>(newy);
    int newtotal = newx * newy;
    short* newbuf = new short[(newtotal)];
    int xdm1 = xdim - 1;
    int ydm1 =ydim - 1;
    if (mode == true)
    {
        int s = 0;
        bool tst = false;
        for (int j = newy - 1; j >= 0; j--)
        {
            double oy = j * invscy;
            int y = int(oy);
            int y1 = int(min((1 + y), ydm1));
            double dy = oy - y;
            double ox = 0;
            int xdm = xdim * y;
            int xdmp =xdim * y1;
            for (int i = 0; i < newx; i++)
            {


                int x = int(ox);
                int x1 = min((1 + x), xdm1);



                double dx = ox - x;

                double c = sprit[x + xdm] * (1 - dy);
                double c1 = sprit[x + xdmp] * (dy);
                double c2 = sprit[x1 + xdm] * (1 - dy);
                double c3 = sprit[x1 + xdmp] * (dy);




                newbuf[s] = short((1 - dx) * (c + c1) + (c2 + c3) * dx);

                s++;
                ox += invscx;
            }
        }

    }
    else
    {
        int ind = 0;
        for (int j = newy - 1; j >= 0; j--)
        {
            double oy = j * invscy;
            int y = min(int(oy), ydm1);
            double ox = 0;
            int yd = xdim * y;
            for (int i = 0; i < newx; i++)
            {


                int x = int(ox);

                short  c = sprit[x + yd];

                newbuf[ind] = c;
                ind++;
                ox += invscx;
            }
        }

    }
    delete[] sprit;
    return newbuf;
    
}

//upscales and scales
short* sprite::applytex(spritec sprit, spritec tex, bool mode,bool aod)
{

   
   int sx = sprit.posscale.x;
   int sy = sprit.posscale.y;
   int sxdim = sprit.file.xdim;
   int sydim = sprit.file.ydim;
   int texdx = tex.file.xdim;
   int texdy = tex.file.ydim;
   int sxd2 = sx / 2;
   int syd2 = sy / 2;
  
 
 float texxd2 = (tex.posscale.x/2);
   float texyd2 = (tex.posscale.y/2);
   int xtpos = tex.pos.x;
   int ytpos = tex.pos.y;
   Vector2 topintl = zerov;
   Vector2 botintr = zerov;
   

  
  
   topintl.x = max(-sxd2 * sxdim, xtpos - texxd2 * texdx);
   topintl.y = min(syd2 * sydim, ytpos + texyd2 * texdy);
botintr.x = min(xtpos+ texxd2 * texdx, sxd2 * sxdim);
   botintr.y = max(ytpos - texyd2 * texdy, -syd2 * sydim);
  
 

   int dy = topintl.y - botintr.y;
   short* buf = new short[sxdim * sydim];
   
       int ind = 0;
       for (int i = 0; i < sxdim*sydim; i++)
       {
       
        
        
              buf[ind] = sprit.file.bufdat[ind];

             
    
               
                      
              
                 
              ind++;
             

           


       }

   


   for (int i = ceil(topintl.x); i < floor(botintr.x); i+=sx)
   {

       for (int j = ceil(botintr.y); j < floor(topintl.y); j+=sy)
       {
           int g = tex.getatpos(Vector2(i, j));

           if (g !=-1)
           {
               int ind = sprit.getatposig(Vector2(i, j));
               char l = tex.file.bufdat[g];
               buf[ind] =max(1,min(16,buf[ind]*l));


           }
          
       }

   }



    return buf;
  
}



sprite::spritec::spritec(const char* fpath, Vector2 pos) :file{ spritefile::spritefile(fpath) }
{


    this->pos = pos;
    this->posscale = Vector2(1, 1);
    
}
//false drawmode = pixelated else it it bilinier interpolated

int sprite::spritec::getatpos(Vector2 pos)
{
    int gh= this->file.xdim;
    int gv = this->file.ydim;
    int xoh = floor(this->posscale.x);
    int yoh = floor(this->posscale.y);
    int xh = floor(this->posscale.x * this->file.xdim / 2);
    int yh = floor(this->posscale.y * this->file.ydim / 2);
    int x = this->pos.x;
    int y = this->pos.y;

    int l = floor(((pos.x - (x - xh)) / xoh)) + this->file.xdim * floor((  yh+pos.y - y) /yoh);

    if (l>=0&&l<gh*gv)
    {


      return l;
    }



    return -1;
}
int sprite::spritec::getatposig(Vector2 pos)
{
    int gh = this->file.xdim;
    int gv = this->file.ydim;
    int xoh = floor(this->posscale.x);
    int yoh = floor(this->posscale.y);
    int xh = floor(this->posscale.x * this->file.xdim / 2);
    int yh = floor(this->posscale.y * this->file.ydim / 2);
    int x = 0;
    int y = 0;

    int l = floor(((pos.x - (x - xh)) / xoh)) + this->file.xdim * floor((yh + pos.y - y) / yoh);

    if (l >= 0 && l < gh * gv)
    {


        return l;
    }



    return -1;
}
