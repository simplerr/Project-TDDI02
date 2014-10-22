#pragma once
#include "BaseState.h"

class Renderer;
class Level;
class Object;
class Texture;
class Player;

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
    Player* mPlayer;
    Texture* mTestBkgd;
};
