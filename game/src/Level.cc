#include "Level.h"
#include "Object.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include "Platform.h"

Level::Level(string filename)
{
    if ( !loadLevel(filename) )
    {
	cerr << "ERROR: MAP FILE: " << filename << "\n";
    };
}

Level::~Level()
{
    for(unsigned int i{}; i < mObjects.size(); ++i)
    {
	delete mObjects[i];
    }
}

void Level::addObject(Object* object)
{
    mObjects.push_back(object);
}

bool Level::loadLevel(string filename)
{
    ifstream input (filename);
    int index, posx, posy, width, height = 0;
    string path = "";
    if( input.is_open() )
    {
	while (input >> index) 
	{
	    if (index == 0) // Player
	    {
		input >> posx >> posy >> width >> height;
		input >> path;
		mObjects.push_back( new Player(Vec2(posx, posy), width, height, path) );
	    }
	    else if (index >= 1) // Platformar
	    {
		input >> posx >> posy >> width >> height;
		input >> path;
		mObjects.push_back( new Platform(Vec2(posx, posy), width, height, path) );
	    }
	}
	
	input.close();
	return true;
    }
    else
    {
	cerr << "Error, kunde inte hitta eller öppna kartan." << filename << "\n";
	return false;
    }
    //vector<Object> Creatures;
    //vector<Object> Platforms;
}

void Level::update(float dt)
{
    // collision
	bool x, y = false;
    for(unsigned int i = 1; i < mObjects.size(); i++) //Börjar på 1 eftersom att Player ligger på 0 (ändra om det ändras)
    {
		
	//Object* objectA = mObjects[i];
	//for(unsigned int j = i; j < mObjects.size(); j++)
	//{
	
	    Object* objectB = mObjects[i];
		
		//##############
		// KOLLA OM KOLLISION FÖR PLAYER X-LED
		mPlayer->setPosition(mPlayer->getPosition().x + mPlayer->getVel().x, mPlayer->getPosition().y);
		if ( mPlayer->collision(mPlayer, objectB) )
		{
			x = true;
		}
		mPlayer->setPosition(mPlayer->getPosition().x - mPlayer->getVel().x, mPlayer->getPosition().y);
		
		// KOLLA OM KOLLISION FÖR PLAYER Y-LED
		mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y + mPlayer->getVel().y);
		if ( mPlayer->collision(mPlayer, objectB) )
		{
			y = true;
		}
		mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y - mPlayer->getVel().y );
		//##############
	  
	  /*  const Platform* pl1 = dynamic_cast<Platform*>(objectA);
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
	    } */	
	//}
    }

	if ( !x ) // OM INGEN KOLLISION MED PLAYER X-LED, UPPDATERA POS X-LED
		mPlayer->setPosition(mPlayer->getPosition().x + mPlayer->getVel().x, mPlayer->getPosition().y);
	if ( !y ) // OM INGEN KOLLISION MED PLAYER Y-LED, UPPDATERA POS Y-LED
		mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y + mPlayer->getVel().y);
		
	//Uppdatering för enskild objekt
    for(unsigned int i = 0; i < mObjects.size(); i++)
    {
	mObjects[i]->update(dt);
    }
	
}

/*
bool Level::collision(Object* objectA, Object* objectB, bool& x, bool& y)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    Vec2 posA = objectA->getPosition();
    Vec2 posB = objectB->getPosition();

    // sides for A
    leftA = posA.x;
    rightA = posA.x + objectA->getWidth();
    topA = posA.y;
    bottomA = posA.y + objectA->getHeight();

    // sides for B
    leftB = posB.x;
    rightB = posB.x + objectB->getWidth();
    topB = posB.y;
    bottomB = posB.y + objectB->getHeight();

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
} */

void Level::draw(Renderer* renderer)
{
    for(unsigned int i = 0; i < mObjects.size(); i++)
	mObjects[i]->draw(renderer);
}

Object* Level::getObjectAt(float x, float y)
{
    return nullptr;
}

Player* Level::findPlayer()
{
    for(unsigned int i{}; i < mObjects.size(); ++i)
    {
	Player* pl = dynamic_cast<Player*>(mObjects[i]);
	if (pl)
	{
	    mPlayer = pl;
	    break;
	}
    }
    return mPlayer;
}
