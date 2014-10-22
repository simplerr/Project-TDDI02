#pragma once

#include <string>
#include <vector>
using namespace std;

class Object;
class Renderer;

class Level
{
public:
  Level(string filename);
  ~Level();

  bool loadLevel(string filename);
  void update(float dt);
  void draw(Renderer* renderer);
  void collision();

  Object* getObjectAt(float x, float y);
 
private:
  vector<Object*> mObjects;
};


