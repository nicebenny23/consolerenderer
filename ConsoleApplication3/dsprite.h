








#ifndef sprite_H
#define sprite_H
#include "vector2.h"
using namespace v2;




namespace spritename {
 
    struct sprite {
    public:
        char* bufdat;
        int xdim;
        int ydim;
        sprite() = default;
        v2::Vector2 pos;
      
      void  operator *=(Vector2 scalev);


      bool inbounds(Vector2 pos);
         sprite(const char* fpath,Vector2 dim);
         sprite(sprite sprit,bool samedat);
         //used for built in stuff
         sprite(const char* buf, Vector2 idim, Vector2 ipos);
         //uses same memory dont use normally it is used for built in stuff
         sprite(char** buf, Vector2 idim);
         
         void flipy();
         void flipx();
     
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
    
    sprite applytex(sprite sprit, sprite tex, Vector2 texpos);
    sprite applytex(sprite sprit, sprite tex, Vector2 texpos, int (*colshade)(int,int));
    sprite scale(sprite sprit,Vector2 scale,int mode);
    bool posinsprite(Vector2 pos);
   
}
#endif