#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "BaseState.h"
#include "Renderer.h"
class Input;

class Game
{
public:
    Game();
    ~Game();

    void changeState(BaseState* state);

    bool initWindow();
    void run();
    
    // räcker det med run() egentligen?
    void update();
    void draw();
    
    void handleEvent(SDL_Event e, bool& exit);

private:
    BaseState* mGameState;
    Renderer* mRenderer;
    Input* mInput;
};

#endif
