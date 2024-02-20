#include "dsprite.h"
#include <iostream>
#include "Renderer.h"
#include "oalgorithm.h"
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "random.h"
#include <fcntl.h>
#include "Colorinfo.h"
using namespace spritename;
using namespace std::chrono;
#pragma warning(disable: 4996)//will not compile without
//load sprite from file


void spritefileload(const char* fpath,sprite &sprit)
{
    char* num;
    FILE* fp;
    struct stat fst;
    sprit.xdim = 0;
    sprit.ydim = 0;
    int len;
    fp = fopen(fpath, "r");
    if (fp == NULL)
    {
        std::exit(-664);
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
            std::exit(-665);
        }
    }

    firstreached = false;
    for (int i = 0; i < secondcomma; i++)
    {
        if (firstreached)
        {
            //shink valforst so i dont have to divide earlyer
            pow2 /= 10;

            sprit.ydim += (num[i] - 48) * pow2;
        }
        else
        {
            if (i >= firstcomma)
            {
                firstreached = true;
                continue;
            }
            pow /= 10;
            sprit.xdim += (num[i] - 48) * pow;
        }
    }



    sprit.bufdat = new char[sprit.xdim * sprit.ydim];

    if (sprit.xdim * sprit.ydim != len - secondcomma - 1)
    {
        std::exit(-666);
    }
    //insert null char

    for (int i = 0; i < sprit.xdim * sprit.ydim; i++)
    {

        sprit.bufdat[i] = num[i + secondcomma + 1] - 97;

    }

    fclose(fp);

}
sprite spritename::scale(sprite sprit, Vector2 scale, int scalmode)
{



    int newx = abs(ceil(sprit.xdim * abs(scale.x)));
    int newy =abs( ceil(sprit.ydim * abs(scale.y)));
    double invscx =abs( sprit.xdim / static_cast<double>(newx));
    double invscy = abs(sprit.ydim / static_cast<double>(newy));
    int newtotal = newx * newy;
    char* newbuf = new char[(newtotal)];
  sprite p=  sprite(&newbuf, Vector2(newx, newy));
  

    int xdm1 = sprit.xdim - 1;
    int ydm1 = sprit.ydim - 1;
    
    if (scalmode == 0)
    {

    
    

        int ind = 0;

        for (int j = 0; j < newy; j++)
        {

            double oy = ((j)*invscy);
            int y = oalgorithm::clamp(round(oy-.5),0,sprit.ydim-1);
            

            int ydint = sprit.xdim * y;
            double ox = 0;
            for (int i = 0; i < newx; i++)
            {

                int oint = int(ox) + ydint;

                char charpos = sprit.bufdat[oint];

                newbuf[ind] = charpos;
                ind++;
                ox += invscx;

            }

        }

    }
  
    if (scalmode >=1)
    {
        int gup = 1;
        int gsid = 1;
        int ind = 0;
        bool mx = false;
        if (scalmode)
        {

        }
        if ((scalmode&2)==2)
        {
            mx = true;
        }
        bool my = false;
        if ((scalmode & 4) == 4)
        {
            my = true;
        }
        for (int j = 0; j < newy ; j++)
        {

            int y = j % int(sprit.ydim);
            

            int ydint = sprit.xdim * y;
            double ox = 0;
            for (int i = 0; i < newx; i++)
            {


                if (ox == sprit.xdim)
                {
                    if (!mx)
                    {
                        ox = 0;
                    }
                    else
                    {
                        ox = sprit.xdim - 1;
                        gsid = -1;
                    }
                }
                if (ox==0)
                {
                    gsid = 1;
                }
                char charpos = sprit.bufdat[int(ox) + ydint];

                newbuf[ind] = charpos;
                ind++;
                ox += gsid;

            }

        }

    }
    if (scale.x < 0)
    {
        p.flipx();
    }
    if (scale.y < 0)
    {
        p.flipy();
    }
  
    return p;
  

}





sprite spritename::applytex(sprite sprit, sprite tex,Vector2 texpos )
{
   
    Vector2 sps = sprit.pos;
    sprit.pos = zerov;
   
   int sxdim = sprit.xdim;
   int sydim = sprit.ydim;
   int texdx = tex.xdim;
   int texdy = tex.ydim;
   int xtpos = tex.pos.x;
   int ytpos = tex.pos.y;
   Vector2 topintl = zerov;
   Vector2 botintr = zerov;
   topintl.x = max(- sxdim/2, xtpos - texdx/2);
   topintl.y = min(sydim/2, ytpos + texdy/2);
   botintr.x = min(xtpos +  texdx/2, sxdim/2);
   botintr.y = max(ytpos-texdy/2, - sydim/2);
 
   int tot = sxdim * sydim;
   char* buf = new char[tot];
   memcpy(buf, sprit.bufdat, tot);

       
   for (float j = (topintl.y)-1; j >=botintr.y ; j-- )
   {
       int tind = tex.getatposig(Vector2(floor((topintl.x)), floor(j)));
      int ind = sprit.getatposig(Vector2(floor(topintl.x), floor(j)));
      for (float i = topintl.x; i < botintr.x; i++)
      { 
          if (tex.bufdat[tind]!=0)
          {
              buf[ind] =0;
          }
          ind++;
          tind++;
       }
   
   }

 
       delete[] tex.bufdat;
     return sprite(&buf,Vector2(sprit.xdim,sprit.ydim));
}

sprite spritename::applytex(sprite sprit, sprite tex,Vector2 texpos, int (*colshade)(int, int))
{
    
   

    int sxdim = sprit.xdim;
    int sydim = sprit.ydim;
    int texdx = tex.xdim;
    int texdy = tex.ydim;
    int xtpos = tex.pos.x;
    int ytpos = tex.pos.y;
    Vector2 topintl = zerov;
    Vector2 botintr = zerov;
    topintl.x = max(-sxdim / 2, xtpos - texdx / 2);
    topintl.y = min(sydim / 2, ytpos + texdy / 2);
    botintr.x = min(xtpos + texdx / 2, sxdim / 2);
    botintr.y = max(ytpos - texdy / 2, -sydim / 2);

    int tot = sxdim * sydim;
    char* buf = new char[tot];
    memcpy(buf, sprit.bufdat, tot);


    for (float j = (topintl.y) - 1; j >= botintr.y; j--)
    {
        int tind = tex.getatposig(Vector2(floor((topintl.x)), floor(j)));
        int ind = sprit.getatposig(Vector2(floor(topintl.x), floor(j)));
        for (float i = topintl.x; i < botintr.x; i++)
        {
            buf[ind]=(*colshade)(buf[ind], tex.bufdat[tind]);
            ind++;
            tind++;
        }

    }

  
        delete[] tex.bufdat;
    
    return sprite(&buf, Vector2(sprit.xdim, sprit.ydim));
}

void sprite::sprite::operator*=(Vector2 scalev)
{

    sprite nbuf = scale(*this, scalev, norm);
    delete[] bufdat;
   *this= nbuf;
}


sprite::sprite(const char* fpath, Vector2 dim) 
{
   
    spritefileload(fpath, *this);

    this->pos = zerov;
   
    
}
spritename::sprite::sprite(sprite sprit, bool samedat)
{

    xdim = sprit.xdim;
    ydim = sprit.ydim;
    int tot = xdim *ydim;
   bufdat = new char[tot];
    memcpy(bufdat, &sprit.bufdat, tot);
    pos = sprit.pos;
   

}
sprite::sprite(const char* buf, Vector2 idim, Vector2 ipos)
{
    xdim = idim.x;
    ydim = idim.y;
    int tot = idim.x * idim.y;
  bufdat = new char[tot];
   
    for (int i = 0; i < tot; i++)
    {
        bufdat[i] = buf[i];
    }
  
    pos = ipos;
   
    
}
spritename::sprite::sprite(char** buf, Vector2 idim)
{
   xdim = idim.x;
   ydim = idim.y;
    int tot = idim.x * idim.y;
 
    
    bufdat = *buf;
  

}

void  sprite::sprite::flipy()
{
   
    int yd2 = ydim / 2;
    int xd = xdim;
    for (int i = 0; i < xdim; i++)
    {
        int p1 = i;
        int p2 = xd * (ydim - 1) + i;
        for (int j = 0; j <yd2; j++)
        {
           
           
            int c = bufdat[p1];
          bufdat[p1] = bufdat[p2];
           bufdat[p2]=c;
            p1 += xd;
            p2 -= xd;
        }
    }

 

}

void spritename::sprite::flipx()
{
    int xd2 = xdim / 2;
    int xd = xdim;
    for (int j = 0; j < ydim; j++)
    {
        int yp = xd * j;
        for (int i = 0; i < xd2; i++)
        {


            int c = bufdat[yp + i];
            int c1 = yp +xd-i-1;
           bufdat[yp+i]=bufdat[c1];
           bufdat[c1] = c;
        }


    }
   

}



int spritename::sprite::getatposig(Vector2 pos)
{
    int gh = this->xdim;
    int gv = this->ydim;

    int xh = floor(1 * this->xdim / 2);
    int yh = floor(1 * this->ydim / 2);
    int x = 0;
    int y = 0;

    int l = floor(((pos.x - x + xh)))+  this->xdim * (gv-1-floor((yh +pos.y - y)));

    if (l >= 0 && l < gh * gv&&x+xh>=pos.x&& x - xh <= pos.x)
    {


        return l;
    }



    return -1;
}
bool spritename::sprite::posinsprite(Vector2 pos)
{
    int gh = this->xdim;
    int gv = this->ydim;

    int xh = floor( gh/ 2);
    int yh = floor( gv / 2);
    int x = 0;
    int y = 0;

    int l = floor((((pos.x - x+xh)))) + this->xdim * (gv - 1 - floor((( yh+pos.y - y))));

    if (l >= 0 && l < gh * gv )
    {
        if ( x +abs( xh)  >= 0 && x - abs(xh) <=0)
        {


            if (this->bufdat[l] != 0)
            {
                return true;
            }
          }
    }



    return false;
}

bool spritename::sprite::inbounds(Vector2 pos)
{
    int gh = this->xdim;
    int gv = this->ydim;

    int xh = floor(4* gh / 2);
    int yh = floor(4 * gv / 2);
    int x = this->pos.x;
    int y = this->pos.y;

  
    if (y + abs(yh) >= pos.y && y - abs(yh) <= pos.y)
    {
        if (x + abs(xh) >= pos.x && x - abs(xh) <= pos.x)
        {


       
                return true;
            
        }
    }



    return false;
}