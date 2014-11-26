#include "Player.h"
#include <iostream>

Player::Player(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    mVelY = 0;
    mVelX = 0;
    setId(Object::PLAYER);
    mSpeed = 6;
    mScore = 0;
    mDead = false;
}

Player::~Player()
{

}

void Player::update(float dt)
{
    //Updaterar pos efter mVel från PlayState
    //setPosition(getPosition().x + mVelX, getPosition().y + mVelY);
    
}

void Player::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Player::handleCollision(Object* object)
{
    //if(object->getId() = 3)
    
    
    
    
    /* 
    //Move the dot left or right
    setPosition(getPosition().x + mVelX, getPosition().y);
	//mCollider.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( collision(this, object) )
    {
        //Move back
        setPosition(getPosition().x - mVelX, getPosition().y);
		//mCollider.x = mPosX;
    }

    //Move the dot up or down
    setPosition(getPosition().x, getPosition().y + mVelY);
	//mCollider.y = mPosY;

    //If the dot collided or went too far up or down
    if( collision(this, object) )
    {
        //Move back
        setPosition(getPosition().x, getPosition().y - mVelY);
		//mCollider.y = mPosY;
    }
    
    return cDetected; */
}

void Player::addVel(int VelX, int VelY)
{
    mVelX += VelX;
    mVelY += VelY;
}

/*void Player::playerJump(int speed)
{
    if(jumpEnable)
    {
        
    }
}*/

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
    setVel(getVel().x * 2,0);
    mSpeed = mSpeed * 2;
}
