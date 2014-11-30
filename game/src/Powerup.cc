#include "Powerup.h"
#include <iostream>

Powerup::Powerup(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    setId(Object::POWERUP);
}

Powerup::~Powerup()
{

}

void Powerup::update(float dt)
{
;
}

void Powerup::draw(Renderer* renderer)
{
    if (!getDead())
        Object::draw(renderer);
}

void Powerup::handleCollision(Object* object)
{

}


Object* Powerup::clone()
{
    Object* NewObject = new Powerup(getPosition(), getWidth(), getHeight(), getFilename());
    return NewObject;
}
