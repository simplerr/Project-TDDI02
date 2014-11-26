#include "MenuState.h"
#include <iostream>
using namespace std;

MenuState::MenuState()
{
	mute = false;
    mMenu = nullptr;
    mAlphaOverlay = nullptr;
}

MenuState::~MenuState()
{
	for (unsigned int i = 0; i < buttonList.size(); i++)
		delete buttonList.at(i);

    delete mMenu;
    delete mAlphaOverlay;
}

void MenuState::init(string initData)
{
	buttonList = {	
		new ButtonImg(Vec2(80, 200), 200, 200, LEVEL1_BUTTON), // Play 1
		new ButtonImg(Vec2(300, 200), 200, 200, LEVEL2_BUTTON), // Play 2
		new ButtonImg(Vec2(520, 200), 200, 200, LEVEL3_BUTTON), // Play 3
		new ButtonImg(Vec2(740, 200), 200, 200, LEVEL3_BUTTON), // Play 3
		new ButtonImg(Vec2(412, 430), 200, 70, CREDIT_BUTTON), // Credit
		new ButtonImg(Vec2(412, 510), 200, 80, EXIT_BUTTON), // Exit
		new ButtonImg(Vec2(SCREEN_WIDTH-100, SCREEN_HEIGHT-100), 100, 100, TOEDITOR_BUTTON),
		new ButtonImg(Vec2(492, 660), 48, 48, VOLUME_BUTTON)
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
		mMenu = renderer->loadTexture(MENU_BACKGROUND);

	if(mAlphaOverlay == nullptr)
	    mAlphaOverlay = renderer->loadTexture("../imgs/alpha.png");
	
	// Renderera ut knapparna
	for (unsigned int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->draw(renderer);
		
		SDL_Rect rect = buttonList[i]->getRect();
		if((i == 1 && getLvlUnlocks() < 1) || (i == 2 && getLvlUnlocks() < 2) || (i == 3 && getLvlUnlocks() < 3))
		    renderer->drawTextureScreen(Vec2(rect.x, rect.y), rect.w, rect.h, mAlphaOverlay);
	}
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
				    setNextState(BaseState::PLAY_STATE, "level1.txt");	
				    break;
				case 1:
				    if (getLvlUnlocks() > 0)
						setNextState(BaseState::PLAY_STATE, "level2.txt");
				    break;
				case 2:
				    if (getLvlUnlocks() > 1)
						setNextState(BaseState::PLAY_STATE, "level3.txt");
				    break;
				case 3:
					if (getLvlUnlocks() > 2)
						setNextState(BaseState::PLAY_STATE, "level4.txt");
				    break;
				case 4:
				    setNextState(BaseState::CREDIT);
				    break;
				case 5:
				    exit = true;
				    break;
				case 6:
				    setNextState(BaseState::EDITOR_STATE);
				    break;
				case 7:
					mute = !mute;
				setMute(mute);
				
					if (!mute) {
						buttonList.at(buttonList.size()-1) = new ButtonImg(Vec2(492, 660), 48, 48, VOLUME_BUTTON);
					} else {
						buttonList.at(buttonList.size()-1) = new ButtonImg(Vec2(492, 660), 48, 48, MUTE_BUTTON);
					}
					break;
				default:
				    break;
				}

			}

		}
	}
}
