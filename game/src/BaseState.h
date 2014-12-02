#ifndef BASESTATE_H
#define BASESTATE_H

#include <SDL2/SDL.h>
#include <string>
using namespace std;
#include "constants.h"

class Renderer;

class BaseState
{
public:
    enum StateId {BASE_STATE, PLAY_STATE, MENU_STATE, PAUSE_STATE, EDITOR_STATE, CREDIT};

 BaseState() : mChangeStateTo(BASE_STATE), mNextStateData("") {};
    virtual ~BaseState() {};

    virtual void init(string initData = "") = 0;
    virtual void cleanup() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(Renderer* renderer) = 0;
    virtual void handleEvent(SDL_Event e, bool& exit, bool& mMuteSound) = 0;  

    StateId changeStateTo() { return mChangeStateTo; } // BASE_STATE don't do anything
    string getNextStateData() { return mNextStateData; }
    void setNextState(StateId nextState, string initData = "") { mChangeStateTo = nextState; mNextStateData = initData;}

	void incLvl() { lvlUnlocks++; }
	int getLvlUnlocks() { return lvlUnlocks; }
private:
    StateId mChangeStateTo;
    string mNextStateData;
};

#endif  
