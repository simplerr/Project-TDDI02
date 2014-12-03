#pragma once

#include "Object.h"
#include "Vec2.h"

class Renderer;

class LavaPlatform : public Object
{
public:
    LavaPlatform(Vec2 pos, int width, int height, string filename);
    ~LavaPlatform();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* &collider);
private:
};
