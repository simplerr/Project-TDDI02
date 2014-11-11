#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object
{
public:
    Player(Vec2 pos, int width, int height, string filename);
    ~Player();

    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* collider);
    void addVel(int VelX, int VelY);
private:
    int mVelX;
    int mVelY;
};

#endif