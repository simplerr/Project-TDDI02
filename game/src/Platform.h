#pragma once
#include "Object.h"

class Renderer;

class Platform : public Object
{
public:
    Platform(Vec2 pos, int width, int height, string filename);
    ~Platform();

    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* collider);
private:
};
