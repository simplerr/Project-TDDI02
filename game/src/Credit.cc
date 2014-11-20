#include "Credit.h"

Credit::Credit()
{
	mBackground = nullptr;
	mExit = nullptr;
}

Credit::~Credit()
{
	delete mBackground;
	delete mExit;
}

void Credit::init()
{
	;
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

	if (mBackground != nullptr && mExit != nullptr) {
		
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mBackground);
		renderer->drawTexture(Vec2(278-100, 560), 620, 110, mExit);
	} else {
		
		mBackground = renderer->loadTexture("../imgs/backgrounds/credit.jpg");
		mExit = renderer->loadTexture("../imgs/backgrounds/creditback.png");
		
	}
}

void Credit::handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
		int x, y;
		SDL_GetMouseState( &x, &y );
		
		if (x > 512-100 && x < 512+100 && y > 560 && y < 670)
			setNextState(BaseState::MENU_STATE);		
	}
}
