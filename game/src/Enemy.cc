#include "Enemy.h"
#include "Player.h"
#include <iostream>

Enemy::Enemy(Vec2 pos, int width, int height, string filename, float endx)
    : Object(pos, width, height, filename)
{
    setId(2);
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
    }
    else if(mDirection == LEFT && getPosition().x < mLeftX)
    {
	setVel(mMoveSpeed, getVel().y);
	mDirection = RIGHT;
    }

    // tmp
    setPosition(getPosition().x + getVel().x, getPosition().y + getVel().y);
}

void Enemy::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Enemy::handleCollision(Object* object)
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
