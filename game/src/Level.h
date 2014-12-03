#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Player.h"
#include "Texture.h"
#include "Projectile.h"
using namespace std;

class Object;
class Renderer;

class Level
{
public:
  Level();
  ~Level();

    void addObject(Object* object); // FOR EDITOR
    void saveObjectList(); // FOR EDITOR
    bool saveLevel(string filename);
    void pop() { mObjects.pop_back(); }
    Object* findObjectByPos(Vec2 mousePos);
    bool isListEmpty();
    void insertion_sort();
    void setCam(int x, int y);
    Vec2 getCam(){ return Vec2(camX, camY); }
    void clearList();
    Vec2 getLevelSize(){ return Vec2(mLEVEL_WIDTH, mLEVEL_HEIGHT); }

    
  Player* findPlayer();
  bool loadLevel(string filename, int k = 1);
  void update(float dt);
  void draw(Renderer* renderer, bool flags = false);

  void setCurrentLevel(string f) { mFilename = f; }
  string getCurrentLevel() { return mFilename; }
  Object* getObjectAt(float x, float y);
  bool getLevelFinish(){ return mLevelFinish; }
  int getPowerupTime(){return mPowerupTime;}
  void addProjectile(Object* shooter);
 
private:
  vector<Object*> mObjects;
  vector<Object*> mBackgrounds;
  vector<Projectile*> mProjectiles;
  Player* mPlayer = nullptr;
  string mFilename;
  int mLEVEL_WIDTH;
  int mLEVEL_HEIGHT;
  unsigned int camX;
  unsigned int camY;
  Texture* mFlagTexture;
  bool mKeyPressed = false;
  bool mLevelFinish;
  const int mPowerupTime = 5; //5 seconds powerup
  Texture* mProjectile{nullptr};
  Texture* mExplosion{nullptr};
};

#endif
