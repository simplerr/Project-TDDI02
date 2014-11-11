#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Platform.h"

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
    // collision
    for(int i = 0; i < mObjects.size(); i++)
    {
	Object* objectA = mObjects[i];
	for(int j = i; j < mObjects.size(); j++)
	{
	    Object* objectB = mObjects[j];

	    const Platform* pl1 = dynamic_cast<Platform*>(objectA);
	    const Platform* pl2 = dynamic_cast<Platform*>(objectB);
	    if(pl1 && pl2)
		continue;

	    bool x_collision = false;
	    bool y_collision = false;
	    if(collision(objectA, objectB, x_collision, y_collision))
	    {
		// for now the moving object is in mObjectList[i] !!OBS!!
		Player* player = dynamic_cast<Player*>(objectA);

		if(player)
		{
		    if(x_collision)
			player->addVel(-player->getVel().x, 0);
		    if(y_collision)
			player->addVel(0, -player->getVel().y);
		    
		    objectA->handleCollision(objectB);
		    objectB->handleCollision(objectA);
		}
	    }	
	}
    }
    

    for(unsigned int i = 0; i < mObjects.size(); i++)
	mObjects[i]->update(dt);
}

bool Level::collision(Object* objectA, Object* objectB, bool& x, bool& y)
{

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
