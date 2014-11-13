#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "BaseState.h"
#include "Renderer.h"
//...
#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
class Input;

class Game
{
public:
    Game();
    ~Game();

    void changeState(BaseState* state);

    bool initWindow();
    void run();
    void cleanup();

    
    // räcker det med run() egentligen?
    void update();
    void draw();
    
    void handleEvent(SDL_Event e, bool& exit);

private:
    BaseState* mGameState;
    PlayState* mPlayState = nullptr;
    MenuState* mMenuState = nullptr;
    PauseState* mPauseState = nullptr;
    Renderer* mRenderer;
    Input* mInput;
	Mix_Music *mMusic;
};

#endif
