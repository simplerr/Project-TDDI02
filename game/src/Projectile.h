#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
#include "Vec2.h"
#include "constants.h"
#include "Texture.h"
#include "Player.h"

class Renderer;

class Projectile : public Object
{
public:
    Projectile(Vec2 pos, bool dir, int id, Texture* projectile, Texture* explosion);
    ~Projectile();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* &collider);
    void handleCollision(Player* &collider);
private:
  Texture* mProjectile;
  Texture* mExplosion;
  bool mDir;
  int mStartPosX;
  int mClipDelay{};
  int mCurrentClip{6};
  int mExplosionCountdown{};
  int mId;
};

#endif