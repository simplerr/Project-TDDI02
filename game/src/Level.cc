#include "Level.h"
#include "Object.h"
#include "Player.h"

Level::Level(string filename)
{
    loadLevel(filename);
}

Level::~Level()
{

}

void Level::addObject(Object* object)
{
    mObjects.push_back(object);
}

Player* Level::addPlayer(int x, int y)
{
    Player* player = new Player(Vec2(x, y), 64, 64, "../imgs/player.jpg");
    addObject(player);
    return player;
}

bool Level::loadLevel(string filename)
{
    return true;
}

void Level::update(float dt)
{
    for(unsigned int i = 0; i < mObjects.size(); i++)
	mObjects[i]->update(dt);
}

void Level::draw(Renderer* renderer)
{
    for(unsigned int i = 0; i < mObjects.size(); i++)
	mObjects[i]->draw(renderer);
}

Object* Level::getObjectAt(float x, float y)
{
    return nullptr;
}
