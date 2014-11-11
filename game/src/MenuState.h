#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"

class MenuState : public BaseState {
 public:
	MenuState();
	~MenuState();

	void init();
	void cleanup();
	void update(float dt);
	void draw(Renderer* renderer);
	void drawCred(Renderer* renderer);
    void handleEvent(SDL_Event e);
 private:
	Texture *mMenu;
	Texture *mPlayButton;
	Texture *mCredit;
};

#endif


