#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Player.h"
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

  Player* findPlayer();
  bool loadLevel(string filename);
  void update(float dt);
  void draw(Renderer* renderer);

  Object* getObjectAt(float x, float y);
 
private:
  vector<Object*> mObjects;
  vector<Object*> mBackgrounds;
  Player* mPlayer;
  string mFilename;
};

#endif
