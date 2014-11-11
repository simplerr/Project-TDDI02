#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "BaseState.h"
#include "Level.h"
#include "Texture.h"
/*
class Renderer;
class Level;
class Object;
class Texture;
class Player;
*/ 
class PlayState : public BaseState
{
public:
    PlayState();
    ~PlayState();

    void init();
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e);
private:
    Level* mLevel;
    Player* mPlayer;
    Texture* mTestBkgd;
    float speed = 2.0;
};

#endif
