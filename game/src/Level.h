#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Player.h"
#include "Texture.h"
#include "Projectile.h"
#include "Finish.h"
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
    void reloadLevel();
    void initTextures(Renderer* renderer);
    
  Player* findPlayer();
  bool loadLevel(string filename, int k = 1);
  void update(float dt);
  void draw(Renderer* renderer, bool flags = false);

  void setCurrentLevel(string f) { mFilename = f; }
  string getCurrentLevel() { return mFilename; }
  Object* getObjectAt(float x, float y);
  bool getLevelFinish(){ return mLevelFinish; }
  void addProjectile(Object* shooter);
  float getTime(){ return mTimer.getSeconds(); }
  void pauseTime() { mTimer.pause(); }
  void startTime() { mTimer.start(); }
  bool getReset() { return mReset; }
 void swichoffReset(){ mReset = false; }
 Texture* getEnemyTexture(){ return mEnemy; }
 Texture* getDeadCreatureTexture(){ return mDeadCreature; }
private:
    Timer mTimer;
  vector<Object*> mObjects;
  vector<Object*> mBackgrounds;
  vector<Projectile*> mProjectiles;
  Player* mPlayer = nullptr;
  Vec2 mPlayerStartPos;
  Finish* mFinish = nullptr;
  string mFilename;
  int mLEVEL_WIDTH;
  int mLEVEL_HEIGHT;
  unsigned int camX;
  unsigned int camY;
  Texture* mFlagTexture;
  bool mKeyPressed = false;
  bool mLevelFinish;
  Texture* mProjectile{nullptr};
  Texture* mExplosion{nullptr};
  Texture* mEnemy{nullptr};
  Texture* mDeadCreature{nullptr};
  Texture* mProjectileEnemy{nullptr};
  bool mReset{false};
};

#endif
