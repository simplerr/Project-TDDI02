#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include "constants.h"

Enemy::Enemy(Vec2 pos, int width, int height, std::string filename, float endx)
    : Object(pos, width, height, filename)
{
    setId(Object::ENEMY);
    mMoveSpeed = 2.0f;
    mEndX = endx;

    if(endx > pos.x)
    {
	mLeftX = pos.x;
	mRightX = endx;
	mDirection = RIGHT;
	setVel(mMoveSpeed, 0);
    }
    else
    {
	mLeftX = endx;
	mRightX = pos.x;
	mDirection = LEFT;
	setVel(-mMoveSpeed, 0);
    }
}

Enemy::~Enemy()
{

}

void Enemy::update(float dt)
{
    if(mDirection == RIGHT && getPosition().x > mRightX)
    { 
	setVel(-mMoveSpeed, getVel().y);
	mDirection = LEFT;
	directionRight = false;
    }
    else if(mDirection == LEFT && getPosition().x < mLeftX)
    {
	setVel(mMoveSpeed, getVel().y);
	mDirection = RIGHT;
	directionRight = true;
    }

    // tmp
    setPosition(getPosition().x + getVel().x, getPosition().y + getVel().y);
	
	    //Animation
    ++mClipDelay;
    if (mClipDelay > 2){
		++mEnemyClip;
		mClipDelay = 0;
		if (mEnemyClip >= 4)
            mEnemyClip = 0;
    }
    // Animation slut
}

void Enemy::draw(Renderer* renderer)
{
	if (!getDead())
	{
		if(mTexture != nullptr)
		{
			renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, ENEMY_CLIPS[mEnemyClip]);
		}
		else
		  mTexture = renderer->loadTexture(getFilename());
	}
	else
		Object::draw(renderer);
}

void Enemy::handleCollision(Object* &object)
{
	object->setPosition(Vec2(0, 0));
}

void Enemy::addVel(float velx, float vely)
{
    mVelX += velx;
    mVelY += vely;
}

Vec2 Enemy::getVel()
{
    return Vec2(mVelX, mVelY);
}

void Enemy::setVel(float velx, float vely)
{
    mVelX = velx;
    mVelY = vely;
}

Object* Enemy::clone()
{
    Object* NewObject = new Enemy(getPosition(), getWidth(), getHeight(), getFilename(), mEndX);
    return NewObject;
}

float Enemy::getEndX()
{
    return mEndX;

}

void Enemy::setEndX(float newEnd)
{
	mEndX = newEnd;
}
