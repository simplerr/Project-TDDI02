#include "Player.h"
#include <iostream>
#include "constants.h"
#include <SDL2/SDL.h>

Player::Player(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    mVelY = 0;
    mVelX = 0;
    setId(Object::PLAYER);
    mSpeed = 6;
    mScore = 0;
    mDead = false;
    mPowerUp = false;
    mPlayerClip = 0;
}

Player::~Player()
{
    ;
}

void Player::reset()
{
    mVelY = 0;
    mVelX = 0;
    setId(Object::PLAYER);
    mSpeed = 6;
    mScore = 0;
    mDead = false;
    mPowerUp = false;
    mPlayerClip = 0;
    setjump(false);
    setfall(true);
}

void Player::update(float dt)
{
    
    if ( !colliedX ) // OM INGEN KOLLISION MED PLAYER X-LED, UPPDATERA POS X-LED
	{
	    setPosition(getPosition().x + mVelX, getPosition().y);
	}
    colliedX = false;
    
    if ( !colliedY ) // OM INGEN KOLLISION MED PLAYER Y-LED, UPPDATERA POS Y-LED
	{
        
	    if(jumping) //Hanterar ifall spelaren är inuti ett hopp
	    {
			mVelY = mVelY +1;
			setPosition(getPosition().x, getPosition().y + mVelY);
	    }
	    else //Hanterar ifall spelaren faller eller ej
	    {
			if(!getfall())
				setfall(true);
                
			mVelY = mVelY + 1;
			setPosition(getPosition().x, getPosition().y + mVelY);
	    }
	}
    colliedY = false;
    
    if(mPowerUp)
        if(getTimer() > POWERUP_TIME)
            powerDown();
    
    //Animation
    ++mClipcounter;
    if (jumping)
        mPlayerClip = 1;
    else if (mVelX == 0)
        mPlayerClip = 0;
    else
    {
        if (mClipcounter > 1)
        {
            ++mPlayerClip;
            mClipcounter = 0;
            if (mPlayerClip >= 10)
                mPlayerClip = 2;
        }
    }
    // Animation slut
}

void Player::draw(Renderer* renderer)
{
    if(mTexture != nullptr)
    {
        if ( mVelX < 0 ) // if moving left
            directionRight = false;
        else if ( mVelX > 0 ) // if moving right
            directionRight = true;
       
        if ( !directionRight ) // if moving left
            renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, PLAYER_CLIP_LEFT[mPlayerClip], false);
        else // if moving right
            renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, PLAYER_CLIP_LEFT[mPlayerClip], true);
    }
    else
      mTexture = renderer->loadTexture(getFilename());
      
}

bool Player::checkCollisionX(Object* &object)
{
    bool temp{false};
    setPosition(getPosition().x + mVelX, getPosition().y); //FLYTTA FRAM
    if ( collision(dynamic_cast<Object*>(this), object) || getPosition().x < 0 ) //KOLLA COLLISION
    {
        colliedX = temp = true;
        //objectColliedX = mObjects[i];
        
    }
    setPosition(getPosition().x - mVelX, getPosition().y); //FLYTTA TBX
    return temp;
}

bool Player::checkCollisionY(Object* &object)
{
    // KOLLA OM KOLLISION FÖR PLAYER Y-LED
    bool temp{false};
    setPosition(getPosition().x, getPosition().y + mVelY ); //FLYTTA FRAM
    if ( collision(dynamic_cast<Object*>(this), object)) //KOLLA COLLISION
    {
        colliedY = temp = true;
        //objectColliedY = mObjects[i];
    }
    setPosition(getPosition().x, getPosition().y - mVelY );//FLYTTA TBX
    return temp;
}

void Player::handleCollisionX(Object* &object)
{
    if (colliedX)
	{
	    if(object->getId() == Object::ENEMY || object->getId() == Object::LAVA_PLATFORM)
	    {
			setDead();
	    }
	    else if(object->getId() == Object::POWERUP)
	    {
			object->setDead();
			powerUp();
	    }
	}
}

void Player::handleCollisionY(Object* &object)
{
    if (colliedY)
	{
		// OBS! Temp, flytta till handleCollision()
		if(object->getId() == Object::LAVA_PLATFORM)
        setDead();
		setjump(false); //Sätter jump till false
        setfall(false);
       

		if( getPosition().y <= object->getPosition().y) //Fixar så att man inte fastnar i platformar men fortrafande buggigt
		{
		    if(object->getId() == Object::ENEMY)
			{
			    object->setDead();
			    incScore();
			    setjump(true);
			}
		    else if(object->getId() == Object::POWERUP)
			{
			    object->setDead();
			    powerUp();
			}
			else
			{
			    setPosition(getPosition().x, object->getPosition().y - getHeight()-1); //om du ska hamna över
			}
		}
		else
		{
		    if(object->getId() == Object::ENEMY)
		    {
                setDead();
		    }
		    else if(object->getId() == Object::POWERUP)
		    {
                object->setDead();
                powerUp();
		    }
            setPosition(getPosition().x, object->getPosition().y+object->getHeight()+1); // om du ska hamna under
            setfall(true); //Sätter hopp till true
		}
	}
}
void Player::handleCollision(Object* &object)
{
    ;
}

void Player::addVel(int VelX, int VelY)
{
    mVelX += VelX;
    mVelY += VelY;
}


Vec2 Player::getVel()
{
    return Vec2(mVelX, mVelY);
}

Object* Player::clone()
{
    Object* NewObject = new Player(getPosition(), getWidth(), getHeight(), getFilename());
    return NewObject;
}

void Player::setjump(bool i)
{
    if(i)
    {
        jumping = true;
        mVelY = -20;
    }
    else
        jumping = false;
}

void Player::setfall(bool i)
{
    if(i)
    {
        falling = true;
        mVelY = 2;
    }
    else
    {
        falling = false;
    }
}

bool Player::getjump()
{
    return jumping;
}

bool Player::getfall()
{
    return falling;
}

void Player::setVel(int x, int y)
{
    mVelX = x;
    mVelY = y;
}

void Player::move(int dir)
{
    if(dir == 1)
	addVel(-mSpeed, 0);
    else if(dir == 2)
	addVel(+mSpeed, 0);
    else if(dir == 3)
	addVel(+mSpeed, 0);
    else if(dir == 4)
	addVel(-mSpeed, 0);
}

void Player::incScore()
{
	mScore++;
}

int Player::getScore()
{
	return mScore;
}

void Player::powerUp()
{
    if(mPowerUp == false)
    {
	mPowerUptime.start();
	mPowerUp = true;
	setVel(getVel().x * 2,0);
	mSpeed = mSpeed * 2;
    }
    if(mPowerUp == true)
    {
	mPowerUptime.reset();
	mPowerUptime.start();
    }
}

void Player::powerDown()
{
    mPowerUp = false;
    mPowerUptime.reset();
    setVel(getVel().x/2, getVel().y);
    mSpeed = mSpeed / 2;
}

