#include "Player.h"

Player::Player(Vec2 pos, int width, int height, string filename)
    : Object(pos, width, height, filename)
{

}

Player::~Player()
{

}

void Player::update(float dt)
{

}

void Player::draw(Renderer* renderer)
{
    Object::draw(renderer);
}

void Player::handleCollision(Object* object)
{

}
