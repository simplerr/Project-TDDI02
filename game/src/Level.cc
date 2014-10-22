#include "Level.h"
#include "Object.h"

Level::Level(string filename)
{
    loadLevel(filename);
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

void Level::draw(Renderer* renderer)
{
    for(int i = 0; i < mObjects.size(); i++)
	mObjects[i]->draw(renderer);
}

Object* Level::getObjectAt(float x, float y)
{
    return nullptr;
}
