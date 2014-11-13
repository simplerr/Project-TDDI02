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

int Object::getWidth()
{
    return mWidth;
}

int Object::getHeight()
{
    return mHeight;
}

bool Object::collision(Object* objectA, Object* objectB)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    Vec2 posA = objectA->getPosition();
    Vec2 posB = objectB->getPosition();

    // sides for A
    leftA = posA.x;
    rightA = posA.x + objectA->getWidth();
    topA = posA.y;
    bottomA = posA.y + objectA->getHeight();

    // sides for B
    leftB = posB.x+2; // ADDERING ÄR FÖR FINJUSTERING
    rightB = posB.x + objectB->getWidth()-1;
    topB = posB.y+2;
    bottomB = posB.y + objectB->getHeight();

    //If any of the sides from A are outside of B
	
	if( bottomA >= topB && topA <= bottomB && rightA >= leftB && leftA <= rightB )
    {
        return true;
    }
    return false;
}
