#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "BaseState.h"
#include "Level.h"
#include "Texture.h"
#include "Button.h"
#include "Timer.h"
#include <vector>

/*
class Renderer;
class Level;
class Object;
class Texture;
class Player;
*/ 

class Highscores;


#define SPEEDBOOSTSEC 6
#define DEFAULTSPEED 6.0
#define BOOSTUPSPEED 9.0

class PlayState : public BaseState
{
public:
    PlayState();
    ~PlayState();

    void init(string initData = "");
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit, bool& mMuteSound);

	void setSpeed(float);
	float getSpeed();

    StateId getStateId() { return PLAY_STATE; }
private:
    Level* mLevel;
    Player* mPlayer;
    Texture* mTestBkgd;
    Texture* mPauseMenu;
    ButtonText* mTimeOnScreen;
    ButtonText* mKilledCreaturesScreen;
    ButtonText* PowerupTimer;
    ButtonText* FPSTimer;
    float speed = 6.0;
    bool mPaused;
    vector<Button*> buttonList;
    Vec2 mousePos;
    int boostSeconds;
    bool boostEnable;
    bool R, L; //Används för Vel bugg...
    Highscores* mHighscores;
    bool mSoundMuted{true};
};

#endif
