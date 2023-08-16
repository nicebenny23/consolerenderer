
#ifndef sprite_H
#define sprite_H
#include "vector2.h"
using namespace v2;

namespace sprite {
    struct spritefile
    {
        char* bufdat;
        int xdim;
        int ydim;
        
        spritefile(const char* fpath);
        spritefile() = default;
    };

    struct spritec {
    public:
        int layer;
        v2::Vector2 com;
        spritec() = default;
        v2::Vector2 pos;
        v2::Vector2 posscale;
      void  operator *=(Vector2 scalev);


      bool  operator<(spritec& sprit);
      bool  operator >= (spritec& sprit);
      bool  operator>(spritec& sprit);
      bool inbounds(Vector2 pos);
         spritec(const char* fpath,Vector2 dim);
         spritec(const char* buf, Vector2 dim, Vector2 pos, Vector2 posscale);
         spritec(char** buf, Vector2 dim, Vector2 pos, Vector2 posscale);//uses same memory dont use normally it is used for built in stuff
         spritec flipy();
         spritec flipx();
        spritefile file;
        bool posinsprite(Vector2 pos);
        int getatposig(Vector2 pos);
    };
    enum scalemode
    {
        norm = 0,
        wrap = 1,
        mx = 2,
        my=4,



    };


    enum texmode {

        mask,
        add,
        mean,

    };
    
    spritec applytex(spritec sprit, spritec tex);
 //   float lerpa(float a, float b, float t);
  //  void shader(spritefile sprit);
    spritec scale(spritec sprit,Vector2 scale,scalemode mode);
    bool posinsprite(Vector2 pos);
   
}
#endif