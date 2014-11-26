#include "Finish.h"

Finish::Finish(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    setId(4);
}

Finish::~Finish()
{

}

void Finish::update(float dt)
{

}

void Finish::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Finish::handleCollision(Object* object)
{

}

Object* Finish::clone()
    {
        Object* NewObject = new Finish(getPosition(), getWidth(), getHeight(), getFilename());
        return NewObject;
    }
