#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "Vec2.h"
#include "Texture.h"
#include "Renderer.h"

using namespace std;


class Object
{
public:
    Object(Vec2 pos, int width, int height, std::string filename);
    virtual ~Object();

    virtual void update(float dt) = 0;
    virtual void draw(Renderer* renderer);
    virtual void handleCollision(Object* collider) = 0;
    virtual bool collision(Object* objectA, Object* objectB);
    
    // add get/set
    Vec2 getPosition();
    int getWidth();
    int getHeight();

    void setPosition(Vec2 pos);
    void setPosition(float x, float y);
private:
    Texture* mTexture;
    Vec2 mPosition;
    string mFilename;
    int mWidth, mHeight;
    int mId;
};

#endif
