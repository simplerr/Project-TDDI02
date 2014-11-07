#include "MenuState.h"

MenuState::MenuState()
{
	mRenderer = new Renderer();
	mMenu = nullptr;
}

void MenuState::init()
{
	mRenderer->initSDL();
}

void MenuState::cleanup()
{
	delete mRenderer;
}

void MenuState::update(float dt)
{
	;
}

void MenuState::draw(Renderer* renderer)
{
	;
}
