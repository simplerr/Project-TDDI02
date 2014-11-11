#include "PauseState.h"

PauseState::PauseState()
{
	currentGame = nullptr;
	mPauseMenu = nullptr;
}

void PauseState::init()
{
	;
}

void PauseState::cleanup()
{
	//delete mRenderer;
}

void PauseState::update(float dt)
{
	;
}

void PauseState::draw(Renderer* renderer)
{
	if (mPauseMenu != nullptr)
		;
	else
		;
}

void PauseState::handleEvent(SDL_Event e)
{
		;
}
