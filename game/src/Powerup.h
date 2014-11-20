#ifndef POWERUP_H
#define POWERUP_H

#include "Object.h"
#include "Vec2.h"

class Renderer;

class Powerup : public Object {
 public:

    Powerup(Vec2 pos, int width, int height, string filename);
    ~Powerup();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* collider);

 private:
	
};

#endif
