
#ifndef sprite_H
#define sprite_H
#include "vector2.h"
using namespace v2;

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
        int layer;
        v2::Vector2 com;
        
        v2::Vector2 pos;
        v2::Vector2 posscale;
      
       
      

        spritec(const char* fpath,Vector2 pos);

      
        spritefile file;
        int getatpos(Vector2 pos);
        int getatposig(Vector2 pos);
    };
    
    short* applytex(spritec sprit, spritec tex, bool mode, bool aod);
 //   float lerpa(float a, float b, float t);
  //  void shader(spritefile sprit);
    short* scale(spritefile sprit,Vector2 scale,bool mode);
    short* scale(short* sprit, Vector2 scale, bool mode,int xdim,int ydim);
}
#endif