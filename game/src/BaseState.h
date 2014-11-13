#ifndef BASESTATE_H
#define BASESTATE_H

#include <SDL2/SDL.h>


class Renderer;

class BaseState
{
public:
    enum StateId {BASE_STATE, PLAY_STATE, MENU_STATE, PAUSE_STATE, EDITOR_STATE};

    BaseState() : mChangeStateTo(BASE_STATE) {};
    virtual ~BaseState() {};

    virtual void init() = 0;
    virtual void cleanup() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(Renderer* renderer) = 0;
    virtual void handleEvent(SDL_Event e, bool& exit) = 0;  

    virtual StateId getStateId() = 0;// { return BASE_STATE; }
    StateId changeStateTo() { return mChangeStateTo; } // BASE_STATE don't do anything
    void setNextState(StateId nextState) { mChangeStateTo = nextState; }
private:
    StateId mChangeStateTo;
};

#endif  
