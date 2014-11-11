#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"
#include "PlayState.h"

class PauseState : public PlayState {
 public:
	PauseState();
	~PauseState();

	void init();
	void cleanup();
	void update(float dt);
	void draw(Renderer* renderer);
    void handleEvent(SDL_Event e);
 private:
	PlayState *currentGame;
	Texture *mPauseMenu;
};

#endif
