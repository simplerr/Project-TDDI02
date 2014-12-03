#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"
#include "Vec2.h"

class Renderer;

class Background : public Object
{
public:
    Background(Vec2 pos, int width, int height, string filename);
    ~Background();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* &collider);
private:
};

#endif