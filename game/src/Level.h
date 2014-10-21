#pragma once

#include <string>
using namespace std;

class Object;

class Level
{
public:
  Level();
  ~Level();

  bool loadLevel(string filename);
  void update(float dt);
  void draw(Renderer* renderer);
  void collision();

  Object* getObjectAt(float x, float y);
 
private:
  vector<Object*> mObjects;
}


