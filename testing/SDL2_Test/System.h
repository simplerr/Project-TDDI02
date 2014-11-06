#ifndef
#define
#include "Object.h"

class System
{
public:
    System(vector<Object>* _v)
        : v(_v), player(_player)
    {
        SDL_Rect* playerRect = player.getTextureRec();
    }

    void handeEvent();
    bool collisionDetection()
    void handleCollision()
    
    bool checkCollision( SDL_Rect a, SDL_Rect b )
private:
    vector<Object>* v;
    Player* player;
    
}

#endif
