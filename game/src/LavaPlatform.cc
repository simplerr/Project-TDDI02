#include "LavaPlatform.h"
#include <iostream>

LavaPlatform::LavaPlatform(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    setId(Object::LAVA_PLATFORM);
}

LavaPlatform::~LavaPlatform()
{

}

void LavaPlatform::update(float dt)
{

}

void LavaPlatform::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void LavaPlatform::handleCollision(Object* object)
{
    std::cout << "collision!" << std::endl;
}

Object* LavaPlatform::clone()
{
    Object* NewObject = new LavaPlatform(getPosition(), getWidth(), getHeight(), getFilename());
    return NewObject;
}
