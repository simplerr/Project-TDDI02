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
	delete mMenu;
	delete mPlayButton;
	delete mExitButton;
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
		renderer->drawTexture(Vec2(512-100, 200), 200, 200, mPlayButton);
		renderer->drawTexture(Vec2(512-100, 450), 200, 100, mExitButton);
	
	}
	else
	{
		mMenu = renderer->loadTexture("../imgs/backgrounds/menu.jpg");
		mPlayButton = renderer->loadTexture("../imgs/PLAY.png");
		mExitButton = renderer->loadTexture("../imgs/EXIT.png");
	}

}

void MenuState::drawCred(Renderer* renderer)
{
	if (mCredit != nullptr)
		renderer->drawTexture(Vec2(400, 400), 400, 200, mCredit);
	else
		mCredit = renderer->loadTexture("../imgs/backgrounds/credit.jpg");
}

void MenuState::handleEvent(SDL_Event e)
{
	;
}
