#include "Object.h"
#include "Renderer.h"

Object::Object(Vec2 pos, int width, int height, string filename)
{
    // todo : assign mId

    mPosition = pos;
    mWidth = width;
    mHeight = height;
    mFilename = filename;
    mTexture = nullptr;
}

Object::~Object()
{
    // cleanup texture
}

void Object::draw(Renderer* renderer)
{
    if(mTexture != nullptr)
	renderer->drawTexture(mPosition, mWidth, mHeight, mTexture);
    else
	mTexture = renderer->loadTexture(mFilename);
}

void Object::setPosition(Vec2 pos)
{
    mPosition = pos;
}

void Object::setPosition(float x, float y)
{
    mPosition = Vec2(x, y);
}

Vec2 Object::getPosition()
{
    return mPosition;
}
