#pragma once
#include "vector2.h"
using namespace v2;
#include "transfom.h"
namespace sprite {
    struct spritefile
    {
        short* bufdat;
        int xdim;
        int ydim;
        
        spritefile(const char* fpath);
    };

    struct spritec {
    public:
        v2::Vector2 com;

        v2::Vector2 pos;
        v2::Vector2 posscale;
      
        short getpixfrompix(Vector2 pos);
      

        spritec(const char* fpath,Vector2 pos);

        void drawtoscreen(bool scalemode, short addcol=0);
        spritefile file;

    };
    float lerpa(float a, float b, float t);
   
    short* scale(spritefile sprit,Vector2 scale,bool mode);
}