#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
#include "Vec2.h"
#include "constants.h"

class Renderer;

class Projectile : public Object
{
public:
    Projectile(Vec2 pos, bool dir);
    ~Projectile();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* collider);
private:
  bool mDir;
  int mStartPosX;
  int mClipDelay{};
  int mCurrentClip{6};
  int mExplosionCountdown{};
  Texture* mExplosionTexture{nullptr};
};

#endif