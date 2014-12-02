#include "PauseState.h"

PauseState::PauseState()
{
	init();
}

PauseState::~PauseState()
{
	for (unsigned int i = 0; i < buttonList.size(); i++)
		delete buttonList.at(i);
}

void PauseState::init()
{
	buttonList = {
		new ButtonImg(Vec2(412, 100), 200, 100, "../imgs/backgrounds/pauseback.png"),
		new ButtonImg(Vec2(412, 400), 200, 100, "../imgs/backgrounds/pausetomenu.png")
	};
}

void PauseState::cleanup()
{
	;
}

void PauseState::update(float dt)
{
	;
}

void PauseState::draw(Renderer* renderer)
{
	for (unsigned int i = 0; i < buttonList.size(); i++)
		buttonList.at(i)->draw(renderer);
}

void PauseState::handleEvent(SDL_Event e, bool& exit, bool& mMuteSound)
{
	if(e.type == SDL_MOUSEBUTTONDOWN) // Kolla musknappnedtryck
    {
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		for (unsigned int i = 0; i < buttonList.size(); i++) {
			
			if (buttonList.at(i)->mouseOver(mousePos)) {

				switch (i) {
				case 0:
					setNextState(BaseState::PLAY_STATE);	
					break;
				case 1:
					setNextState(BaseState::MENU_STATE);
					break;
				default:
					break;
				}

			}

		}

	}

}
