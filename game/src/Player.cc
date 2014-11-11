#include "Player.h"

Player::Player(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{
    mVelY = 0;
    mVelX = 0;
}

Player::~Player()
{

}

void Player::update(float dt)
{
    //Updaterar pos efter mVel från PlayState
    setPosition(getPosition().x + mVelX, getPosition().y + mVelY);
    
}

void Player::draw(Renderer* renderer)
{
    Object::draw(renderer);
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
