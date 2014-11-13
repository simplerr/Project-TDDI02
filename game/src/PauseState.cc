#include "PauseState.h"

PauseState::PauseState()
{
	//currentGame = nullptr;
	mPauseMenu = nullptr;
}

PauseState::~PauseState()
{
	delete mPauseMenu;
}

void PauseState::init()
{
	;
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
	if (mPauseMenu != nullptr)
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mPauseMenu);
	else
		mPauseMenu = renderer->loadTexture("../imgs/backgrounds/pause.png");
}

void PauseState::handleEvent(SDL_Event e, bool& exit)
{
    if(e.key.keysym.sym == SDLK_UP) // GÅ TILLBAKA TILL SPELET
    {
	setNextState(BaseState::PLAY_STATE);
    }
    else if (e.key.keysym.sym == SDLK_DOWN) // GÅ TILL MENYN OCH AVSLUTA NIVÅN
    {
	setNextState(BaseState::MENU_STATE);
    }
}
