#ifndef FINISH_H
#define FINISH_H

#include "Object.h"
#include "Vec2.h"
#include "Player.h"

class Renderer;

class Finish : public Object
{
public:
    Finish(Vec2 pos, int width, int height, string filename);
    ~Finish();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* &collider);
    bool checkFinish(Player* collider);
private:
};

#endif