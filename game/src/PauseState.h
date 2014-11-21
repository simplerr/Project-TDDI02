#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"
#include "PlayState.h"
#include "Button.h"
#include <vector>

class PauseState : public BaseState {
 public:
    PauseState();
    ~PauseState();

    void init();
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit);

    StateId getStateId() { return PAUSE_STATE; }
 private:
    vector<Button*> buttonList;
	Vec2 mousePos;
};

#endif
