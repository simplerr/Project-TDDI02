#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Vec2.h"

class Player : public Object
{
public:
    Player(Vec2 pos, int width, int height, string filename);
    ~Player();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* collider);
    void addVel(int VelX, int VelY);
    void setjump(int i);
    void setfall(int i);
    bool getfall();
    bool getjump();
    void setVel(int x, int y);
    void move(int dir);
    
    //void playerJump(int speed)

    Vec2 getVel();
private:
    int mVelX;
    int mVelY;
    bool jumping;
    bool falling;
    int mSpeed;
};

#endif
