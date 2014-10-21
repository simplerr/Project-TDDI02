#include "Object.h"

Object::Object(Vec2 pos, int width, int height, Texture* texture)
{
    // todo : assign mId

    mPosition = pos;
    mWidth = width;
    mHeight = height;
    mTexture = texture;
}

Object::~Object()
{
    // cleanup texture
}
