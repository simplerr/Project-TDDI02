#include "MenuState.h"
#include <iostream>

MenuState::MenuState()
{
	;
}

void MenuState::init()
{
	mRenderer = new Renderer();
	
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
