#pragma once
#include "Vec2.h"

class Renderer;
class Texture;

class Object
{
public:
    Object(Vec2 pos, int width, int height, Texture* texture);
    virtual ~Object();

    virtual void update(float dt) = 0;
    virtual void draw(Renderer* renderer) = 0;
    virtual void handleCollision(Object* collider) = 0;
    
    // add get/set
private:
    Texture* mTexture;
    Vec2 mPosition;
    int mWidth, mHeight;
    int mId;
};
