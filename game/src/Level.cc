#include "Level.h"
#include "Object.h"

Level::Level()
{

}

Level::~Level()
{

}

bool Level::loadLevel(string filename)
{
    return true;
}

void Level::update(float dt)
{
    for(int i = 0; i < mObjects.size(); i++)
	mObjects[i]->update(dt);
}

void draw(Renderer* renderer)
{
    for(int i = 0; i < mObjects.size(); i++)
	mObjects[i]->draw(renderer);
}

Object* getObjectAt(float x, float y)
{
    return nullptr;
}
