#include "MenuState.h"

MenuState::MenuState()
{
    mMenu = nullptr;
    mPlayButton = nullptr;
    mExitButton = nullptr;
	mEditorButton = nullptr;
    mCredit = nullptr;
	init();
}

MenuState::~MenuState()
{
    delete mMenu;
    delete mPlayButton;
    delete mExitButton;
	delete mEditorButton;
    delete mCredit;
}

void MenuState::init()
{
	;
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
	if(mMenu != nullptr && mPlayButton != nullptr &&  mExitButton != nullptr && mEditorButton != nullptr )
	{
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mMenu);
		renderer->drawTexture(Vec2(512-100, 200), 200, 200, mPlayButton);
		renderer->drawTexture(Vec2(512-100, 550), 200, 100, mExitButton);
		renderer->drawTexture(Vec2(SCREEN_WIDTH-100, SCREEN_HEIGHT-100), 100, 100, mEditorButton);
		renderer->drawTexture(Vec2(512-100, 420), 200, 100, mCredit);
	
	}
	else
	{
		mMenu = renderer->loadTexture("../imgs/backgrounds/menu.jpg");
		mPlayButton = renderer->loadTexture("../imgs/PLAY.png");
		mExitButton = renderer->loadTexture("../imgs/EXIT.png");
		mEditorButton = renderer->loadTexture("../imgs/toEditor.png");
		mCredit = renderer->loadTexture("../imgs/backgrounds/credit.png");
	}

}

void MenuState::handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_MOUSEBUTTONDOWN) // SPELA KARTA
    {
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );
			
		if (x > 512-100 && x < 512+100 && y > 200 && y < 400) //Klickområde STARTA SPELET
		{
			setNextState(BaseState::PLAY_STATE);
		}
		if (x > 512-100 && x < 512+100 && y > 420 && y < 500) //Klickområde CREDIT
		{
			setNextState(BaseState::CREDIT);
		}
		if ( x > 512-100 && x < 512+100 && y > 500 && y < 650 ) // Klickområde AVSLUTA PROGRAMMET
			exit = true;
		if ( x > SCREEN_WIDTH-100 && x < SCREEN_WIDTH && y > SCREEN_HEIGHT-100 && y < SCREEN_HEIGHT ) // Klickområde till editor
			setNextState(BaseState::EDITOR_STATE);
	}

}
