#include "MenuState.h"

MenuState::MenuState()
{
	//mRenderer = new Renderer();
	mMenu = nullptr;
}

void MenuState::init()
{
	;
}

void MenuState::cleanup()
{
	//delete mRenderer;
}

void MenuState::update(float dt)
{
	;
}

void MenuState::draw(Renderer* renderer)
{
	 // draw test bkgd
    if(mMenu != nullptr && mPlayButton != nullptr)
    {
	renderer->drawTexture(Vec2(0, 0), 1024, 768, mMenu);
	renderer->drawTexture(Vec2(200, 200), 200, 200, mPlayButton);
	
    }
    else
    {
	mMenu = renderer->loadTexture("../imgs/backgrounds/menu.jpg");
	mPlayButton = renderer->loadTexture("../imgs/PLAY.png");
    }
		
}

void MenuState::handleEvent(SDL_Event e)
{
		;
}