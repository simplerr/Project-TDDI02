#include <fstream>
#include <iostream>
#include "constants.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Powerup.h"
#include "Enemy.h"
#include "Platform.h"
#include "Background.h"
#include "Decoration.h"

Level::Level()
{
	camX=SCREEN_WIDTH/2;
	camY=SCREEN_HEIGHT/2;
	mFlagTexture = nullptr;
}

Level::~Level()
{
    for(unsigned int i{}; i < mObjects.size(); ++i)
    {
	delete mObjects[i];
    }
	for(unsigned int i{}; i < mBackgrounds.size(); ++i)
    {
	delete mBackgrounds[i];
    }
}

void Level::addObject(Object* object)
{
    mObjects.push_back(object);
}

bool Level::loadLevel(string filename, int k)
{
	mFilename = filename;
    ifstream input (mFilename);
    int index, posx, posy, width, height = 0;
    string path = "";
	
    if( input.is_open() )
    {
		input >> width >> height;
		mLEVEL_WIDTH = width;
		mLEVEL_HEIGHT = height;
		while (input >> index) 
		{
			input >> posx >> posy >> width >> height;
			input >> path;
			if (index == 0) // Player
			    mObjects.push_back( new Player(Vec2(posx, posy), width, height, path) );
			else if (index == 1) // Platformar
			    mObjects.push_back( new Platform(Vec2(posx, posy), width, height, path) );
			else if (index == 2) // Fiender
			{
			    float endx;
			    input >> endx;
			    mObjects.push_back( new Enemy(Vec2(posx, posy), width, height, path, endx) );
			}
			else if (index == 3) // Powerups
				mObjects.push_back( new Powerup(Vec2(posx, posy), width, height, path) );
			else if ( k == 1 ) // Play 
			{
				if (index == 4) // Decoration
					mBackgrounds.push_back( new Decoration(Vec2(posx, posy), width, height, path) );
				else if (index == 5) // Backgrounds
					mBackgrounds.push_back( new Background(Vec2(posx, posy), width, height, path) );
			}
			else if ( k == 2 ) // Editor 
			{
				if (index == 4) // Decoration
					mObjects.push_back( new Decoration(Vec2(posx, posy), width, height, path) );
				else if (index == 5) // Backgrounds
					mObjects.push_back( new Background(Vec2(posx, posy), width, height, path) );
			}
			else
				cerr << "FEL, objekt okänt\n";
		}
	
	input.close();
	return true;
    }
    else
    {
	cerr << "Error, kunde inte hitta eller öppna kartan. Filnamn som söktes: " << mFilename << "\n";
	return false;
    }
    //vector<Object> Creatures;
    //vector<Object> Platforms;
}

bool Level::saveLevel(string filename)
{
    int maxHeight{}, maxWidth{}, temp{};
    mFilename = filename;
    ofstream output (mFilename);
    if( output.is_open() )
    {
	// LOOPA IGOM OBJECT FÖR ATT BESTÄMMA LEVEL_HEIGHT OCH LEVEL_WIDTH
	for(unsigned int k{}; k < mObjects.size(); ++k)
	{
	    temp = mObjects[k]->getPosition().x + mObjects[k]->getWidth(); // Objects right
	    if( temp > maxWidth )
		maxWidth = temp;
	    temp = mObjects[k]->getPosition().y + mObjects[k]->getHeight(); // Objects bottom
	    if( temp > maxHeight )
		maxHeight = temp;
	}
	// KOLLA SÅ ATT INTE LEVEL ÄR FÖR LITEN FÖR SKÄRMEN
	if ( maxWidth < SCREEN_WIDTH )
	    output << SCREEN_WIDTH;
	else
	    output << maxWidth;
	output << " ";
	if ( maxHeight < SCREEN_HEIGHT )
	    output << SCREEN_HEIGHT;
	else
	    output << maxHeight;
	output << "\n";
	
	// SPARA ALLA OBJEKT
	for(unsigned int i{}; i < mObjects.size(); ++i)
	{
	    
	    if (mObjects[i]->getId() == 0)
		output << "0 ";
	    else if (mObjects[i]->getId() == 1)
		output << "1 ";
	    else if (mObjects[i]->getId() == 2)
		output << "2 ";
	    else if (mObjects[i]->getId() == 3)
		output << "3 ";
	    else if (mObjects[i]->getId() == 4)
		output << "4 ";
		else if (mObjects[i]->getId() == 5)
		output << "5 ";
	    
	    output << mObjects[i]->getPosition().x << " " << mObjects[i]->getPosition().y << " " << mObjects[i]->getWidth() << " "
		   << mObjects[i]->getHeight() << " " << mObjects[i]->getFilename();

	    if(mObjects[i]->getId() == 2)
	    {
		Enemy* enemy = dynamic_cast<Enemy*>(mObjects[i]);
		output << " " << enemy->getEndX() << "\n"; 
	    }
	    else
		output << "\n";
	}
	output.close();
	return true;
    }
    else
    {
	cerr << "Error, kunde inte öppna kartan vid save. Filnamn som söktes: " << mFilename << "\n";
	return false;
    }
    //vector<Object> Creatures;
    //vector<Object> Platforms;
}

Object* Level::findObjectByPos(Vec2 mousePos)
{
    int objectLeft, objectRight, objectUpper, objectBottom;
    Object* found = nullptr;
    Object* lowestFound = nullptr;
    for(unsigned int i{}; i < mObjects.size(); ++i)
    {
	objectUpper = mObjects[i]->getPosition().y;
	objectBottom = mObjects[i]->getPosition().y + mObjects[i]->getHeight();
	objectLeft = mObjects[i]->getPosition().x;
	objectRight = mObjects[i]->getPosition().x + mObjects[i]-> getWidth();
	
	if ( mousePos.y > objectUpper && mousePos.x > objectLeft && mousePos.y < objectBottom && mousePos.x < objectRight )
	{
	    //Fixar så man får det översta objectet som är placerat
	    found = mObjects[i];
	    if (lowestFound != nullptr)
	    {
		if (lowestFound->getId() >= found->getId() )
		    lowestFound = found;
	    }
	    else
		lowestFound = found;	
	}
    }
    
    if(lowestFound != nullptr)
    {
	found = lowestFound->clone();
	for(unsigned int z{}; z < mObjects.size(); ++z)
	{
	    if (lowestFound == mObjects[z])
	    {
		for(unsigned int j{z+1}; j < mObjects.size(); ++j)
		{
		    std::swap(mObjects[j], mObjects[j-1]);
		}
		break;
	    }
	}
	
	mObjects.resize(mObjects.size()-1);
	mObjects.shrink_to_fit();
	return found;
    }
    return nullptr;
    
    
    
    //return nullptr;
}

bool Level::isListEmpty()
{
	if ( mObjects.size() == 0 )
		return true;
	return false;
}

void Level::insertion_sort()
{
	int length = mObjects.size();
	int i, j;
	Object* tmp;
	for (i = 1; i < length; i++)
	{
		j = i;
		while (j > 0 && mObjects[j - 1]->getId() < mObjects[j]->getId())
		{
			tmp = mObjects[j];
			mObjects[j] = mObjects[j - 1];
			mObjects[j - 1] = tmp;
			j--;
		}
	}
}

void Level::setCam(int x, int y)
{
    camX = camX + x;
    camY = camY + y;
	if ( camX < SCREEN_WIDTH/2 )
		camX = SCREEN_WIDTH/2;
	if (camY < SCREEN_HEIGHT/2 )
		camY = SCREEN_HEIGHT/2;
}

void Level::update(float dt)
{	
    // collision
	bool x, y = false;
	Object* objectColliedY;
	Object* objectColliedX;
	int yColID;
	int xColID;
    for(unsigned int i = 0; i < mObjects.size()-1; i++) //Börjar på 1 eftersom att Player ligger på 0 (ändra om det ändras)
    {
		
		if(mPlayer == mObjects[i]) //Så att den inte kollar kollision med sig själv...
			continue;
		
		//##############
		// KOLLA OM KOLLISION FÖR PLAYER X-LED3
		mPlayer->setPosition(mPlayer->getPosition().x + mPlayer->getVel().x, mPlayer->getPosition().y); //FLYTTA FRAM
		if ( mPlayer->collision(mPlayer, mObjects[i]) || mPlayer->getPosition().x < 0 ) //KOLLA COLLISION
		{
			x = true;
			objectColliedX = mObjects[i];
		}
		mPlayer->setPosition(mPlayer->getPosition().x - mPlayer->getVel().x, mPlayer->getPosition().y); //FLYTTA TBX
		// KOLLA OM KOLLISION FÖR PLAYER Y-LED
		mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y + mPlayer->getVel().y); //FLYTTA FRAM
		if ( mPlayer->collision(mPlayer, mObjects[i])) //KOLLA COLLISION
		{
			y = true;
			objectColliedY = mObjects[i];
		}
		mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y - mPlayer->getVel().y );//FLYTTA TBX
		//##############
		
		
    }
	if ( !x ) // OM INGEN KOLLISION MED PLAYER X-LED, UPPDATERA POS X-LED
	{
	    mPlayer->setPosition(mPlayer->getPosition().x + mPlayer->getVel().x, mPlayer->getPosition().y);
	}
	else
	{
	    xColID = objectColliedX->getId();
	    cout << xColID << endl;
	    if(xColID = 2)
	    {
		setalive();
	    }
	    else if(xColID = 3)
	    {
		
	    }
	    mPlayer->setVel(mPlayer->getVel().x, mPlayer->getVel().y);
	    
	}
	
	if ( !y ) // OM INGEN KOLLISION MED PLAYER Y-LED, UPPDATERA POS Y-LED
	{
	    if(mPlayer->getjump()) //Hanterar ifall spelaren är inuti ett hopp
	    {
			mPlayer->setVel(mPlayer->getVel().x, mPlayer->getVel().y +1);
			mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y + mPlayer->getVel().y);
	    }
	    else //Hanterar ifall spelaren faller eller ej
	    {
			if(!mPlayer->getfall())
			{
				mPlayer->setfall(1);
			}
			else if(mPlayer->getfall())
			{
				mPlayer->setVel(mPlayer->getVel().x, mPlayer->getVel().y + 1);
				mPlayer->setPosition(mPlayer->getPosition().x, mPlayer->getPosition().y + mPlayer->getVel().y);
			}
	    }
	}
	else
	{
		mPlayer->setjump(2); //Sätter fall till false
		
		yColID = objectColliedY->getId();
		
		if( mPlayer->getVel().y >= 0 ) //Fixar så att man inte fastnar i platformar men fortrafande buggigt
		{
			mPlayer->setfall(2); //Sätter hopp till false
			mPlayer->setPosition(mPlayer->getPosition().x, objectColliedY->getPosition().y-mPlayer->getHeight()); //om du ska hamna över
		}
		else
		{
			mPlayer->setPosition(mPlayer->getPosition().x, objectColliedY->getPosition().y+objectColliedY->getHeight()); // om du ska hamna under
			mPlayer->setfall(1); //Sätter hopp till true
		}
	}
	
	//Uppdatering för enskild objekt
    for(unsigned int i = 0; i < mObjects.size(); i++)
    {
		mObjects[i]->update(dt);
	}
} // END OF UPDATE

void Level::draw(Renderer* renderer, bool flags)
{
	if ( mPlayer != nullptr )
		renderer->updateCamera(mPlayer->getPosition().x, mPlayer->getPosition().y, mPlayer->getWidth(), mPlayer->getHeight(), mLEVEL_WIDTH, mLEVEL_HEIGHT);
	else{
		renderer->updateCamera(camX, camY, 0, 0, 10000, 10000);
	}
	for(unsigned int i = 0; i < mBackgrounds.size(); i++)
		mBackgrounds[i]->draw(renderer);
    for(unsigned int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->draw(renderer);
		if (mObjects[i]->getId() == 2 && flags == true)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(mObjects[i]);
			if (enemy->getEndX() != enemy->getPosition().x)
			{
				if(mFlagTexture == nullptr)
					mFlagTexture = renderer->loadTexture("../imgs/flag.png");
	
				renderer->drawTextureScreen(Vec2(enemy->getEndX(), enemy->getPosition().y), 48, 48, mFlagTexture);
			}
		}
    }
} // END OF DRAW()

Object* Level::getObjectAt(float x, float y)
{
    return nullptr;
}

Player* Level::findPlayer()
{
    for(unsigned int i{}; i < mObjects.size(); ++i)
    {
		if (mObjects[i]->getId() == 0)
		{
			mPlayer = dynamic_cast<Player*>(mObjects[i]);
			break;
		}
    }
    return mPlayer;
}

void Level::clearList()
{
	if ( !isListEmpty() )
	{
		for(unsigned int i{}; i < mObjects.size(); ++i)
		{
			delete mObjects[i];
		}
		mObjects.resize(0);
	}
}

void Level::setalive()
{
    alive = !alive;
}

bool Level::getalive()
{
    return alive;
}