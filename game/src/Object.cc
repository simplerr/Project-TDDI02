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
