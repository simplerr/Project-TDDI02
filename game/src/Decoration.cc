#include "Decoration.h"

Decoration::Decoration(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    setId(Object::DECORATION);
}

Decoration::~Decoration()
{

}

void Decoration::update(float dt)
{

}

void Decoration::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Decoration::handleCollision(Object* object)
{

}

Object* Decoration::clone()
    {
        Object* NewObject = new Decoration(getPosition(), getWidth(), getHeight(), getFilename());
        return NewObject;
    }
