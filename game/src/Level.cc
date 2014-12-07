#include <fstream>
#include <iostream>
#include "constants.h"
#include "Level.h"
#include "Object.h"
#include "Powerup.h"
#include "Enemy.h"
#include "Platform.h"
#include "Background.h"
#include "Decoration.h"
#include "LavaPlatform.h"

Level::Level()
{
	camX=SCREEN_WIDTH/2;
	camY=SCREEN_HEIGHT/2;
	mFlagTexture = nullptr;
	mLevelFinish = false;
	mTimer.start();
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
	for(unsigned int i{}; i < mProjectiles.size(); ++i)
    {
		delete mProjectiles[i];
    }
	delete mFlagTexture;
	delete mProjectile;
	delete mExplosion;
}

void Level::addObject(Object* object)
{
    mObjects.push_back(object);
}

bool Level::loadLevel(string filename, int mode)
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
			if (index == Object::PLAYER) // Player
			{
				if (mode == 2)
					mObjects.push_back( new Player(Vec2(posx, posy), width, height, path) );
				else
				{
					mPlayer = new Player(Vec2(posx, posy), width, height, path);
					mPlayerStartPos = Vec2(posx, posy);
				}
			}
			else if (index == Object::PLATFORM) // Platformar
			    mObjects.push_back( new Platform(Vec2(posx, posy), width, height, path) );
			else if (index == Object::ENEMY) // Fiender
			{
			    float endx;
			    input >> endx;
			    mObjects.push_back( new Enemy(Vec2(posx, posy), width, height, path, endx) );
			}
			else if (index == Object::POWERUP) // Powerups
			    mObjects.push_back( new Powerup(Vec2(posx, posy), width, height, path) );
			else if(index == Object::LAVA_PLATFORM)			
			    mObjects.push_back(new LavaPlatform(Vec2(posx, posy), width, height, path));      
			else if (index == Object::FINISH) // Powerups
			{
				if (mode == 2)
					mObjects.push_back( new Finish(Vec2(posx, posy), width, height, path) );
				else
					mFinish = new Finish(Vec2(posx, posy), width, height, path);
			}
			else if ( mode == 1 ) // Play 
			{
			    if (index == Object::DECORATION) // Decoration
				mBackgrounds.push_back( new Decoration(Vec2(posx, posy), width, height, path) );
			    else if (index == Object::BACKGROUND) // Backgrounds
				mBackgrounds.push_back( new Background(Vec2(posx, posy), width, height, path) );
			}
			else if ( mode == 2 ) // Editor 
			{
			    if (index == Object::DECORATION) // Decoration
				mObjects.push_back( new Decoration(Vec2(posx, posy), width, height, path) );
			    else if (index == Object::BACKGROUND) // Backgrounds			       
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
	    output << mObjects[i]->getId() << " ";
	    output << mObjects[i]->getPosition().x << " " << mObjects[i]->getPosition().y << " " << mObjects[i]->getWidth() << " "
		   << mObjects[i]->getHeight() << " " << mObjects[i]->getFilename();

	    if(mObjects[i]->getId() == Object::ENEMY)
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
	if (mPlayer->getPosition().y + mPlayer->getHeight() > mLEVEL_HEIGHT || mPlayer->getDead()) // Trillar spelaren ned, ladda om banan
	{
		reloadLevel(); // (Kan behövas ändras)
	}
	
    // collision
	Object* colliedX{nullptr};
	Object* colliedY{nullptr};

    for(unsigned int i = 0; i < mObjects.size(); i++) //Börjar på 1 eftersom att Player ligger på 0 (ändra om det ändras)
    {
		if(mObjects[i]->getDead())
			continue;
		
		for(unsigned int p = 0; p < mProjectiles.size(); p++)
		{
			mProjectiles[p]->handleCollision(mObjects[i]);
		}
		
		if ( mObjects[i]->getId() == Object::ENEMY ) // FIENDERS PROJEKTILER
			{
				if (rand() % ENEMY_SHOOT_CHANCE == 1)
				{
					addProjectile(mObjects[i]);
				}
			}
		
		if( mPlayer->checkCollisionX(mObjects[i]) )
			colliedX = mObjects[i];
		
		if ( mPlayer->checkCollisionY(mObjects[i]) )
			colliedY = mObjects[i];
		
		mObjects[i]->update(dt);
	} // END OF OBJECT LOOP
	
	mPlayer->handleCollisionX(colliedX);
	mPlayer->handleCollisionY(colliedY);
	mPlayer->update(dt);
	
	mLevelFinish = mFinish->checkFinish(mPlayer);
	
	for(unsigned int p = 0; p < mProjectiles.size(); p++)
	{
		if (PROJECTILES_COLLISION_EACHOTHER)
		{
			for(unsigned int k = p+1; k < mProjectiles.size(); k++)
				mProjectiles[p]->handleCollision(mProjectiles[k]);
		}
		mProjectiles[p]->update(dt);
		mProjectiles[p]->handleCollision(mPlayer);
	}
	
} // END OF UPDATE

void Level::draw(Renderer* renderer, bool flags)
{
	initTextures(renderer);
	// UPPDATERAR SMART-KAMERA
	if ( mPlayer != nullptr )
		renderer->updateCamera(mPlayer->getPosition().x, mPlayer->getPosition().y, mPlayer->getWidth(), mPlayer->getHeight(), mLEVEL_WIDTH, mLEVEL_HEIGHT);
	else
		renderer->updateCamera(camX, camY, 0, 0, 10000, 10000);
		
	if (!flags)
	{
		// RITAR UT BAKGRUNDER OCH DEKORATIONER
		for(unsigned int i = 0; i < mBackgrounds.size(); i++)
			mBackgrounds[i]->draw(renderer);
	}		
	// RITAR UT ALLA PLATFORMAR OCH FIENDER SAMT POWERUPS
    for(unsigned int i = 0; i < mObjects.size(); i++)
	{
		mObjects[i]->draw(renderer);
		if (mObjects[i]->getId() == Object::ENEMY && flags == true) // SPECIALFALL: OM flags = sant, RITAR UT SLUTPOS FÖR FIENDER...(för EDITOR)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(mObjects[i]);
			if (enemy->getEndX() != enemy->getPosition().x)
			{
				if(mFlagTexture == nullptr)
					mFlagTexture = renderer->loadTexture("../imgs/flag.png");
		
				renderer->drawTexture(Vec2(enemy->getEndX(), enemy->getPosition().y), 48, 48, mFlagTexture);
			}
		}
    }
	if (!flags)
	{
		// RITAR UT PROJEKTILER
		for(unsigned int p = 0; p < mProjectiles.size(); p++)
		{
			mProjectiles[p]->draw(renderer);
		}
		mFinish->draw(renderer); 
		mPlayer->draw(renderer);
	}
	
} // END OF DRAW()

Object* Level::getObjectAt(float x, float y)
{
    return nullptr;
}

Player* Level::findPlayer()
{
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

void Level::addProjectile(Object* shooter)
{
	Texture* projectileTexture; 
	if (shooter->getId() == 2)
		projectileTexture = mProjectile;
	else
		projectileTexture  = mProjectileEnemy;
		
	if(shooter->directionRight)
		mProjectiles.push_back(new Projectile(Vec2( shooter->getPosition().x, shooter->getPosition().y+10 ), shooter->directionRight, shooter->getId(), projectileTexture, mExplosion ));
	else
		mProjectiles.push_back(new Projectile(Vec2( shooter->getPosition().x, shooter->getPosition().y+10 ), shooter->directionRight, shooter->getId(), projectileTexture, mExplosion ));
	
}

void Level::reloadLevel()
{
	for(unsigned int i{}; i < mProjectiles.size(); ++i)
    {
		delete mProjectiles[i];
    }
	mProjectiles.resize(0);
	for(unsigned int i{}; i < mObjects.size(); ++i)
	{
		mObjects[i]->setAlive();
		mObjects[i]->DeadClipCounterReset();
	}
	mPlayer->setPosition(mPlayerStartPos);
	mPlayer->reset();
	mTimer.reset();
	mReset = true;
}
void Level::initTextures(Renderer* renderer)
{
	if(mProjectile == nullptr || mExplosion == nullptr || mEnemy == nullptr || mDeadCreature == nullptr )
	{
		mProjectile = renderer->loadTexture(PROJECTILE_YELLOW_FILEPATH);
		mProjectileEnemy = renderer->loadTexture(PROJECTILE_RED_FILEPATH);
		mExplosion = renderer->loadTexture(EXPLOSION_FILEPATH);
		mEnemy = renderer->loadTexture(FILEPATH_ENEMY1);
		mDeadCreature = renderer->loadTexture(BLOODSPLATTER);
	}
}