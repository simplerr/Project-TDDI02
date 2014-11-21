#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "Renderer.h"
#include "Texture.h"
#include "Button.h"
#include <vector>

class MenuState : public BaseState {
public:
    MenuState();
    ~MenuState();

    void init();
    void cleanup();
    void update(float dt);
    void draw(Renderer* renderer);
    void handleEvent(SDL_Event e, bool& exit);

    StateId getStateId() { return MENU_STATE; }
private:
    Texture *mMenu;
	vector<Button*> buttonList;
	Vec2 mousePos;
};

#endif

