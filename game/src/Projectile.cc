#include "Projectile.h"
#include <iostream>

Projectile::Projectile(Vec2 pos, bool dir, int id, Texture* projectile, Texture* explosion)
    : Object(pos, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, ""), mProjectile(projectile), mExplosion(explosion)
{
    setId(Object::PLATFORM);
    mDir = dir;
    mStartPosX = pos.x;
    mId = id;
}

Projectile::~Projectile()
{
    ;
}

void Projectile::update(float dt)
{
    if( !getDead() )
    {
        int speed;
        if ( mId == 0 )
            speed = PLAYER_PROJECTILE_SPEED;
        else
            speed = ENEMY_PROJECTILE_SPEED;
            
        if (mDir == 0)
            setPosition(getPosition().x-speed, getPosition().y);
        else
            setPosition(getPosition().x+speed, getPosition().y);
    }
    
}

void Projectile::draw(Renderer* renderer)
{
    if ( !getDead() )
    {
        if (!mDir)
            renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mProjectile, PROJECTILE_CLIPS[mCurrentClip++], true );
        else
            renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mProjectile, PROJECTILE_CLIPS[mCurrentClip++], false );
        
        if (mCurrentClip >= PROJECTILE_NUM_CLIPS)
            mCurrentClip = 2;
    }
    else
    {
        if(mExplosionCountdown < EXPLOSION_NUM_CLIPS)
        {
            if (!mDir)
                renderer->drawTextureAnimation(Vec2( getPosition().x-20, getPosition().y), EXPLOSION_DIAMETER, EXPLOSION_DIAMETER, mExplosion, EXPLOSION_CLIPS[mExplosionCountdown++], false);
            else
                renderer->drawTextureAnimation(Vec2( getPosition().x+30, getPosition().y), EXPLOSION_DIAMETER, EXPLOSION_DIAMETER, mExplosion, EXPLOSION_CLIPS[mExplosionCountdown++], false);
        }
    }
    //PROJECTILE_WIDTH
}

void Projectile::handleCollision(Projectile* &object)
{
    if ( !getDead() && mId != object->getId())
    {
        if(collision(this, dynamic_cast<Object*>(object)))
        {
                object->setDead();
                setDead();
        }
        else if ( mDir && getPosition().x > mStartPosX+PROJECTILE_LENGTH )
            setDead();
        else if ( !mDir && getPosition().x < mStartPosX-PROJECTILE_LENGTH )
            setDead();
    }
}

void Projectile::handleCollision(Player* &object)
{
    if ( !getDead() && mId != object->getId())
    {
        if(collision(this, dynamic_cast<Object*>(object)))
        {
                object->setDead();
                setDead();
        }
        else if ( mDir && getPosition().x > mStartPosX+PROJECTILE_LENGTH )
            setDead();
        else if ( !mDir && getPosition().x < mStartPosX-PROJECTILE_LENGTH )
            setDead();
    }
}

void Projectile::handleCollision(Object* &object)
{
    if ( !getDead() && mId != object->getId())
    {
        if(collision(this, object))
        {
            if (object->getId() == Object::ENEMY || object->getId() == Object::PLAYER )
            {
                object->setDead();
                setDead();
            }
            else if (object->getId() == Object::PLATFORM )
                setDead();
        }
        else if ( mDir && getPosition().x > mStartPosX+PROJECTILE_LENGTH )
            setDead();
        else if ( !mDir && getPosition().x < mStartPosX-PROJECTILE_LENGTH )
            setDead();
    }
}

Object* Projectile::clone()
    {
        Object* NewObject = new Projectile(getPosition(), mDir, mId, mProjectile, mExplosion );
        return NewObject;
    }
