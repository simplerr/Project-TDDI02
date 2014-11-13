#include "PauseState.h"

PauseState::PauseState()
{
	//currentGame = nullptr;
	mPauseMenu = nullptr;
}

PauseState::~PauseState()
{
	//currentGame = nullptr;
	delete mPauseMenu;
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
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mPauseMenu);
	else
		mPauseMenu = renderer->loadTexture("../imgs/backgrounds/pause.png");
}

void PauseState::handleEvent(SDL_Event e)
{
		;
}
