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
		new ButtonImg(Vec2(212, 200), 200, 200, "../imgs/backgrounds/level1.png"), // Play 1
		new ButtonImg(Vec2(422, 200), 200, 200, "../imgs/backgrounds/level2.png"), // Play 2
		new ButtonImg(Vec2(632, 200), 200, 200, "../imgs/backgrounds/level3.png"), // Play 3
		new ButtonImg(Vec2(412, 430), 200, 70, "../imgs/backgrounds/creditbutton.png"), // Credit
		new ButtonImg(Vec2(412, 510), 200, 80, "../imgs/backgrounds/exitbutton.png"), // Exit
		new ButtonImg(Vec2(SCREEN_WIDTH-100, SCREEN_HEIGHT-100), 100, 100, "../imgs/toEditor.png"),
		new ButtonImg(Vec2(492, 660), 48, 48, "../imgs/volume.png")
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
		mMenu = renderer->loadTexture("../imgs/backgrounds/mainmenu.jpg");

	if(mAlphaOverlay == nullptr)
	    mAlphaOverlay = renderer->loadTexture("../imgs/alpha.png");
	
	// Renderera ut knapparna
	for (unsigned int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->draw(renderer);
		
		SDL_Rect rect = buttonList[i]->getRect();
		if((i == 1 && getLvlUnlocks() < 1) || (i == 2 && getLvlUnlocks() < 2))
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
				    setNextState(BaseState::CREDIT);
				    break;
				case 4:
				    exit = true;
				    break;
				case 5:
				    setNextState(BaseState::EDITOR_STATE);
				    break;
				case 6:
					mute = !mute;
					setMute(mute);
					
					if (!mute) 
						buttonList.at(buttonList.size()-1) = new ButtonImg(Vec2(492, 660), 48, 48, "../imgs/volume.png");
				    else 
						buttonList.at(buttonList.size()-1) = new ButtonImg(Vec2(492, 660), 48, 48, "../imgs/mute.png");

					break;
				default:
				    break;
				}

			}

		}
	}
}
