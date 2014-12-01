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

void Player::update(float dt)
{
    
    //Animation
    ++mClipcounter;
        if (jumping)
            mPlayerClip = 1;
        else if (mVelX == 0)
        {
            mPlayerClip = 0;
        }
        else
        {
            if (mClipcounter > 1){
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
            leftOrRight = false;
        else if ( mVelX > 0 ) // if moving right
            leftOrRight = true;
       
        if ( !leftOrRight ) // if moving left
            renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, PLAYER_CLIP_LEFT[mPlayerClip]);
        else // if moving right
            renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, PLAYER_CLIP_RIGHT[mPlayerClip]);
    }
    else
      mTexture = renderer->loadTexture(getFilename());
}

void Player::handleCollision(Object* object)
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

void Player::setjump(int i)
{
    if(i==1)
    {
	jumping = true;
	mVelY = -20;
    }
    else
	jumping = false;
}

void Player::setfall(int i)
{
    if(i==1)
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

