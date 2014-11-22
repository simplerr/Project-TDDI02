#include "Credit.h"

Credit::Credit()
{
    mBackground = nullptr;
}

Credit::~Credit()
{
	delete mBack;
	delete mBackground;
}

void Credit::init(string initData)
{
	mBack = new ButtonImg(Vec2(300, SCREEN_HEIGHT-175), 420, 80, "../imgs/backgrounds/creditback.png");
}

void Credit::cleanup()
{
	;
}

void Credit::update(float dt)
{
	
}

void Credit::draw(Renderer* renderer)
{
	renderer->updateCamera(0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (mBackground != nullptr) 		
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mBackground);
	else 		
		mBackground = renderer->loadTexture("../imgs/backgrounds/credit.jpg");
		
	mBack->draw(renderer);
}

void Credit::handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		
		if (mBack->mouseOver(mousePos)) 
			setNextState(BaseState::MENU_STATE);		
	}
}
