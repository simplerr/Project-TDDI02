#pragma once
#include <string>
#include "Vec2.h"

using namespace std;

class Renderer;
class Texture;

class Object
{
public:
    Object(Vec2 pos, int width, int height, std::string filename);
    virtual ~Object();

    virtual void update(float dt) = 0;
    virtual void draw(Renderer* renderer);
    virtual void handleCollision(Object* collider) = 0;
    
    // add get/set
private:
    Texture* mTexture;
    Vec2 mPosition;
    string mFilename;
    int mWidth, mHeight;
    int mId;
};
