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
    void handleEvent(SDL_Event e, bool& exit);

    StateId getStateId() { return PLAY_STATE; }
private:
    Level* mLevel;
    Player* mPlayer;
    Texture* mTestBkgd;
    Texture* mPauseMenu;
    float speed = 3.0;
    bool mPaused;
};

#endif
