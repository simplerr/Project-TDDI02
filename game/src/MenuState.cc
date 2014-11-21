#include "MenuState.h"
#include "constants.h"

MenuState::MenuState()
{
    mMenu = nullptr;
	init();
}

MenuState::~MenuState()
{
	for (unsigned int i = 0; i < buttonList.size(); i++)
		delete buttonList.at(i);

    delete mMenu;
}

void MenuState::init()
{
	buttonList = {	
		new ButtonImg(Vec2(212, 200), 200, 200, "../imgs/backgrounds/level1.png"), // Play 1
		new ButtonImg(Vec2(422, 200), 200, 200, "../imgs/backgrounds/level1.png"), // Play 2
		new ButtonImg(Vec2(632, 200), 200, 200, "../imgs/backgrounds/level1.png"), // Play 3
		new ButtonImg(Vec2(412, 430), 200, 100, "../imgs/backgrounds/credit.png"), // Credit
		new ButtonImg(Vec2(412, 550), 200, 100, "../imgs/EXIT.png"), // Exit
		new ButtonImg(Vec2(SCREEN_WIDTH-100, SCREEN_HEIGHT-100), 100, 100, "../imgs/toEditor.png")
	};
}

void MenuState::cleanup()
{
	;
}

void MenuState::update(float dt)
{
	;
}

void MenuState::draw(Renderer* renderer)
{
	//set camera to normal pos
	renderer->updateCamera(0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); 
	// draw test bkgd
	if(mMenu != nullptr)
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mMenu);
	else
		mMenu = renderer->loadTexture("../imgs/backgrounds/menu.jpg");
	
	// Renderera ut knapparna
	for (unsigned int i = 0; i < buttonList.size(); i++)
		buttonList[i]->draw(renderer);
}

void MenuState::handleEvent(SDL_Event e, bool& exit)
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
					setNextState(BaseState::PLAY_STATE);
					break;
				case 2:
					setNextState(BaseState::PLAY_STATE);
					break;
				case 3:
					setNextState(BaseState::CREDIT);
					break;
				case 4:
					exit = true;
					break;
				case 5:
					setNextState(BaseState::EDITOR_STATE);
					break;
				default:
					break;
				}

			}

		}
	}
}
