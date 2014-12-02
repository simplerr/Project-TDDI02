#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
#include "Vec2.h"

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
  int mProjectileSpeed{15};
  bool mDir;
  int mStartPosX;
  int mClipDelay{};
  int mCurrentClip{6};
  
};

#endif