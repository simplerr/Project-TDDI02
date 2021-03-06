#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"
#include "Button.h"
#include "Level.h"
#include <vector>

class Highscores;

class MenuState : public BaseState {
public:
    MenuState();
    ~MenuState();

    void init(string initData = "");
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit, bool& mMuteSound);
	
    StateId getStateId() { return MENU_STATE; }
private:
    Texture *mMenu;
    Texture *mAlphaOverlay;
    vector<Button*> buttonList;
    Vec2 mousePos;
    bool mute;
    Highscores* mHighscores;
    string mHooverLevel;
    ButtonText* mHighscoreButtonT;
	ButtonText* mHighscoreButtonS;
    bool mSoundMuted{false};
};

#endif

