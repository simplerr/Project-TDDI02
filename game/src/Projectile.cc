#include "Projectile.h"
#include <iostream>

Projectile::Projectile(Vec2 pos, bool dir)
    : Object(pos, PROJECTILE_WIDTH, PROJECTILE_HEIGHT, PROJECTILE_FILEPATH)
{
    setId(Object::PLATFORM);
    mDir = dir;
    mStartPosX = pos.x;
}

Projectile::~Projectile()
{
    delete mExplosionTexture;
}

void Projectile::update(float dt)
{
    if( !getDead() )
    {
        if (mDir == 0)
            setPosition(getPosition().x-PROJECTILE_SPEED, getPosition().y);
        else
            setPosition(getPosition().x+PROJECTILE_SPEED, getPosition().y);
        
        //Animation
        ++mClipDelay;
         if (mClipDelay > 1)
         {
            ++mCurrentClip;
            mClipDelay = 0;
            if (mCurrentClip >= PROJECTILE_NUM_CLIPS)
                mCurrentClip = 0;
        }   
         // Animation slut
    }
    
}

void Projectile::draw(Renderer* renderer)
{
    if ( !getDead() )
    {
        if(mTexture != nullptr)
		{
            if (!mDir)
                renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, PROJECTILE_CLIPS[mCurrentClip], true);
            else
                renderer->drawTextureAnimation(getPosition(), getWidth(), getHeight(), mTexture, PROJECTILE_CLIPS[mCurrentClip], false);
		}
		else
            mTexture = renderer->loadTexture(getFilename());
    }
    else
    {
        if(mExplosionCountdown <= EXPLOSION_NUM_CLIPS)
        {
            if(mExplosionTexture != nullptr)
            {
                if (!mDir)
                    renderer->drawTextureAnimation(Vec2( getPosition().x-40, getPosition().y), EXPLOSION_DIAMETER, EXPLOSION_DIAMETER, mExplosionTexture, EXPLOSION_CLIPS[mExplosionCountdown++], false);
                else
                    renderer->drawTextureAnimation(Vec2( getPosition().x+40, getPosition().y), EXPLOSION_DIAMETER, EXPLOSION_DIAMETER, mExplosionTexture, EXPLOSION_CLIPS[mExplosionCountdown++], false);
            }
            else
                mExplosionTexture = renderer->loadTexture(EXPLOSION_FILEPATH);
        }
    }
    //PROJECTILE_WIDTH
}

void Projectile::handleCollision(Object* object)
{
    if ( !getDead() )
    {
        if(collision(this, object))
        {
            if (object->getId() == Object::ENEMY )
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
        Object* NewObject = new Projectile(getPosition(), mDir);
        return NewObject;
    }
