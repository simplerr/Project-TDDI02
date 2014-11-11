#ifndef EDITROSTATE_H
#define EDITORSTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"

class EditorState : public BaseState {
 public:
	EditorState();
	~EditorState();

	void init();
	void cleanup();
	void update(float dt);
	void draw(Renderer* renderer);
    void handleEvent(SDL_Event e);
 private:
	Texture *mMenu;
	Level *mLevel;
};

#endif


