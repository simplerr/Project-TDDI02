#include "Platform.h"

Platform::Platform(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{

}

Platform::~Platform()
{

}

void Platform::update(float dt)
{

}

void Platform::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Platform::handleCollision(Object* object)
{

}
