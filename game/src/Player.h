#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Vec2.h"
#include "Timer.h"

class Player : public Object
{
public:
    Player(Vec2 pos, int width, int height, string filename);
    ~Player();

    Object* clone();
    
    void update(float dt);
    void draw(Renderer* renderer);
    void handleCollision(Object* &collider);
    void addVel(int VelX, int VelY);
    void setjump(bool i);
    void setfall(bool i);
    bool getfall();
    bool getjump();
    void setVel(int x, int y);
    void move(int dir);
    void powerUp();
    void powerDown();
    void setDead() { mDead = !mDead; }
    bool getDead() { return mDead; }
    bool getPowerUp() { return mPowerUp; }
    float getTimer() { return mPowerUptime.getSeconds(); }
    bool checkCollisionX(Object* &object);
    bool checkCollisionY(Object* &object);
    void handleCollisionX(Object* &collider);
    void handleCollisionY(Object* &collider);
	void incScore();
	int getScore();
    void reset();

    Vec2 getVel();
private:
    int mVelX;
    int mVelY;
    bool jumping;
    bool falling;
    int mSpeed;
    int mScore;
    bool mDead;
    bool mPowerUp;
    Timer mPowerUptime;
    int mClipcounter{}; // == EN DELAY FÖR ANIMATIONEN
    int mPlayerClip;
    bool colliedX{false};
    bool colliedY{false};
    
};

#endif
