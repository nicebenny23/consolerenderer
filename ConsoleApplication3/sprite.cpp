#include "sprite.h"
#include <iostream>
#include "Renderer.h"

#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "random.h"
#include <fcntl.h>
#include "Colorinfo.h"
using namespace sprite;
using namespace std::chrono;
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

    

    bufdat = new char[xdim * ydim + 1];

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
spritec sprite::scale(spritec sprit, Vector2 scale, scalemode mode)
{
    int newx = abs(ceil(sprit.file.xdim * abs(scale.x)));
    int newy =abs( ceil(sprit.file.ydim * abs(scale.y)));
    double invscx =abs( sprit.file.xdim / static_cast<double>(newx));
    double invscy = abs(sprit.file.ydim / static_cast<double>(newy));
    int newtotal = newx * newy;
    char* newbuf = new char[(newtotal)];
    int xdm1 = sprit.file.xdim - 1;
    int ydm1 = sprit.file.ydim - 1;
    
    if (mode == 0)
    {

    
    

        int ind = 0;

        for (int j = 0; j < newy; j++)
        {
            double oy = j * invscy;
            int y = floor(oy);


            int ydint = sprit.file.xdim * y;
            double ox = 0;
            for (int i = 0; i < newx; i++)
            {

                int oint = int(ox) + ydint;

                char charpos = sprit.file.bufdat[oint];

                newbuf[ind] = charpos;
                ind++;
                ox += invscx;

            }

        }

    }
    if (mode >=1)
    {
        int gup = 1;
        int gsid = 1;
        int ind = 0;
        bool mx = false;
        if (mode)
        {

        }
        if ((mode&2)==2)
        {
            mx == true;
        }
        bool my = false;
        if ((mode & 4) == 4)
        {
            my == true;
        }
        for (int j = 0; j < newy ; j++)
        {

            int y = j % int(sprit.file.ydim);


            int ydint = sprit.file.xdim * y;
            double ox = 0;
            for (int i = 0; i < newx; i++)
            {


                if (ox == sprit.file.xdim)
                {
                    if (!mx)
                    {
                        ox = 0;
                    }
                    else
                    {
                        ox = sprit.file.xdim - 1;
                        gsid = -1;
                    }
                }
                if (ox==0)
                {
                    gsid = 1;
                }
                char charpos = sprit.file.bufdat[int(ox) + ydint];

                newbuf[ind] = charpos;
                ind++;
                ox += gsid;

            }

        }

    }

  return  spritec(&newbuf, Vector2(newx, newy),sprit.pos,Vector2(1,1));
  

}





spritec sprite::applytex(spritec sprit, spritec tex)
{
    if (tex.posscale.x!=1||tex.posscale.y!=1)
    {
        tex  = scale(tex, Vector2(tex.posscale.x, tex.posscale.y),norm);
        tex.file.xdim = ceil(tex.file.xdim*tex.posscale.x);
        tex.file.ydim = ceil(tex.file.ydim * tex.posscale.y);

    }
    Vector2 sps = sprit.pos;
    sprit.pos = zerov;
   
   int sxdim = sprit.file.xdim;
   int sydim = sprit.file.ydim;
   int texdx = tex.file.xdim;
   int texdy = tex.file.ydim;
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
   memcpy(buf, sprit.file.bufdat, tot);

       
   for (float j = (topintl.y)-1; j >=botintr.y ; j-- )
   {
       int tind = tex.getatposig(Vector2(floor((topintl.x)), floor(j)));
      int ind = sprit.getatposig(Vector2(floor(topintl.x), floor(j)));
      for (float i = topintl.x; i < botintr.x; i++)
      { 
          if (tex.file.bufdat[tind]!=0)
          {
              buf[ind] =0;
          }
          ind++;
          tind++;
       }
   
   }

   if (tex.posscale.x != 1 || tex.posscale.y != 1)
   {
       delete[] tex.file.bufdat;
   }
    return spritec(&buf,Vector2(sprit.file.xdim,sprit.file.ydim), sps,sprit.posscale);
}



void sprite::spritec::operator*=(Vector2 scalev)
{

    spritec nbuf = scale(*this, scalev, norm);
    delete[] file.bufdat;
   *this= nbuf;
}

bool sprite::spritec::operator<(spritec& sprit)
{
    return(layer < sprit.layer?true:false);
}

bool sprite::spritec::operator>=(spritec& sprit)
{
    return(layer >= sprit.layer ? true : false);
}
bool sprite::spritec::operator>(spritec& sprit)
{
    return(layer > sprit.layer ? true : false);
}

sprite::spritec::spritec(const char* fpath, Vector2 dim) :file{ spritefile::spritefile(fpath) }
{


    this->pos = zerov;
    this->posscale = Vector2(1, 1);
    
}
spritec::spritec(const char* buf, Vector2 dim, Vector2 pos, Vector2 posscale)
{
    file.xdim = dim.x;
    file.ydim = dim.y;
    int tot = dim.x * dim.y;
    file.bufdat = new char[tot];
    layer = 0;
    for (int i = 0; i < tot; i++)
    {
        file.bufdat[i] = buf[i];
    }
  
    pos = zerov;
    posscale =unitv;
    
}
sprite::spritec::spritec( char** buf, Vector2 dim, Vector2 pos, Vector2 posscale)
{
    file.xdim = dim.x;
    file.ydim = dim.y;
    int tot = dim.x * dim.y;
 
    layer = 0;
    file.bufdat = *buf;
    pos = zerov;
    posscale = unitv;

}

spritec sprite::spritec::flipy()
{
    spritec sprit = *this;
    int yd2 = file.ydim / 2;
    int xd = file.xdim;
    for (int i = 0; i < file.xdim; i++)
    {
        int p1 = i;
        int p2 = xd * (sprit.file.ydim - 1) + i;
        for (int j = 0; j <yd2; j++)
        {
           
           
            int c = sprit.file.bufdat[p1];
            sprit.file.bufdat[p1] = sprit.file.bufdat[p2];
            sprit.file.bufdat[p2]=c;
            p1 += xd;
            p2 -= xd;
        }
    }

    return sprit;

}

spritec sprite::spritec::flipx()
{
    spritec sprit = *this;
    int xd2 = file.xdim / 2;
    int xd = file.xdim;
    for (int j = 0; j < file.ydim; j++)
    {
        int yp = xd * j;
        for (int i = 0; i < xd2; i++)
        {


            int c = file.bufdat[yp + i];
            int c1 = yp +xd-i-1;
            sprit.file.bufdat[yp+i]=file.bufdat[c1];
            sprit.file.bufdat[c1] = c;
        }


    }
    return sprit;

}



int sprite::spritec::getatposig(Vector2 pos)
{
    int gh = this->file.xdim;
    int gv = this->file.ydim;

    int xh = floor(1 * this->file.xdim / 2);
    int yh = floor(1 * this->file.ydim / 2);
    int x = this->pos.x;
    int y = this->pos.y;

    int l = floor(((pos.x - x + xh)))+  this->file.xdim * (gv-1-floor((yh +pos.y - y)));

    if (l >= 0 && l < gh * gv&&x+xh>=pos.x&& x - xh <= pos.x)
    {


        return l;
    }



    return -1;
}
bool sprite::spritec::posinsprite(Vector2 pos)
{
    int gh = this->file.xdim;
    int gv = this->file.ydim;

    int xh = floor( this->posscale.x*gh/ 2);
    int yh = floor( this->posscale.y*gv / 2);
    int x = this->pos.x;
    int y = this->pos.y;

    int l = floor((((pos.x - x+xh)/this->posscale.x))) + this->file.xdim * (gv - 1 - floor((( yh+pos.y - y)/this->posscale.y)));

    if (l >= 0 && l < gh * gv )
    {
        if ( x +abs( xh)  >= pos.x && x - abs(xh) <= pos.x)
        {


            if (this->file.bufdat[l] != 0)
            {
                return true;
            }
          }
    }



    return false;
}

bool sprite::spritec::inbounds(Vector2 pos)
{
    int gh = this->file.xdim;
    int gv = this->file.ydim;

    int xh = floor(this->posscale.x * gh / 2);
    int yh = floor(this->posscale.y * gv / 2);
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