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
    void handleEvent(SDL_Event e);
 private:
	//Renderer *mRenderer; Varför ett till renderer när Game har en?
	Texture *mMenu;
};

#endif
