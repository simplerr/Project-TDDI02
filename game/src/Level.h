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

  void addObject(Object* object); // FOR EDITOR
  void saveObjectList(); // FOR EDITOR
  
  //Player* addPlayer(int x, int y);

  Player* findPlayer();
  bool loadLevel(string filename);
  void update(float dt);
  void draw(Renderer* renderer);
  //bool collision(Object* objectA, Object* objectB, bool& x, bool& y);

  Object* getObjectAt(float x, float y);
 
private:
  vector<Object*> mObjects;
  Player* mPlayer;
};

#endif
