#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
using namespace std;

class Object;
class Renderer;
class Player;

class Level
{
public:
  Level(string filename);
  ~Level();

  void addObject(Object* object);
  
  //Player* addPlayer(int x, int y);

  bool loadLevel(string filename);
  void update(float dt);
  void draw(Renderer* renderer);
  void collision();

  Object* getObjectAt(float x, float y);
 
private:
  vector<Object*> mObjects;
  Player* mplayer;
};

#endif