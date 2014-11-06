#ifndef GAME_H
#define GAME_H

class BaseState;
class Renderer;
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

private:
    BaseState* mGameState;
    Renderer* mRenderer;
    Input* mInput;
};

#endif
