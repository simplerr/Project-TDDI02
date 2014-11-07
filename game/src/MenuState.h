#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "Renderer.h"

class MenuState : public BaseState {
 public:
	MenuState();
	~MenuState();

	void init();
	void cleanup();
	void update(float dt);
	void draw(Renderer* renderer);
 private:
	Renderer *mRenderer;
};

#endif
