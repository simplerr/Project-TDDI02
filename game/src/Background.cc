#include "Background.h"

Background::Background(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    setId(Object::BACKGROUND);
}

Background::~Background()
{

}

void Background::update(float dt)
{

}

void Background::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Background::handleCollision(Object* object)
{

}

Object* Background::clone()
    {
        Object* NewObject = new Background(getPosition(), getWidth(), getHeight(), getFilename());
        return NewObject;
    }
