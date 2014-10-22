#pragma once
#include "BaseState.h"

class Renderer;
class Level;
class Texture;

class PlayState : public BaseState
{
public:
    PlayState();
    ~PlayState();

    void init();
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
private:
    Level* mLevel;
    Texture* mTestBkgd;
};
