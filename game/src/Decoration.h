#ifndef DECORATION_H
#define DECORATION_H

#include "Object.h"
#include "Vec2.h"

class Renderer;

class Decoration : public Object
{
public:
    Decoration(Vec2 pos, int width, int height, string filename);
    ~Decoration();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* collider);
private:
};

#endif