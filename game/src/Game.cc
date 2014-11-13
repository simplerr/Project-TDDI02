#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Renderer.h"
#include "BaseState.h"

Game::Game()
{
    mRenderer = new Renderer;
	
	mMenuState = new MenuState;
	mMenuState->init();
	mGameState = mMenuState;
}
 
Game::~Game()
{
  //delete mGameState;
    delete mRenderer;
}

bool Game::initWindow()
{
    // init the window using SDL
	mMusic = Mix_LoadMUS("../sounds/Hits_from_the_bong.mp3");
	if (!mMusic)
		return false;
	return mRenderer->initSDL();
}

void Game::cleanup()
{
	// VET EJ OM DETTA ÄR RÄTT, MINNESLÄCKA VID AVSLUT AV PROGRAM KAN FÖREKOMMA
	mPlayState->cleanup();
	mPlayState = nullptr;
	mMenuState->cleanup();
	mMenuState = nullptr;
	mPauseState->cleanup();
	mPauseState = nullptr;
	
}
void Game::changeState(BaseState* state)
{
    // init the new one
    mGameState = state;
}

void Game::run()
{
    // TODO
    // make sure the game runs at 60 fps
    float dt = 0.0f;

    // update the current gamestate
    mGameState->update(dt);
    
    // all rendering should happen between beginScene() and endScene()
    mRenderer->beginScene();



	// #########################
	//Kom gärna på en bättre lösning om möjligt att rendra PlayState bakom PauseState
	const PauseState* pause = dynamic_cast<const PauseState*>(mGameState);
	if(pause)
		mPlayState->draw(mRenderer);
	// #########################
	
	// draw the current gamestate
	mGameState->draw(mRenderer);
	
    mRenderer->endScene();
}

void Game::update()
{

}

void Game::draw()
{

}


void Game::handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_QUIT)
        exit = true;
		
	const MenuState* menu = dynamic_cast<const MenuState*>(mGameState);
	const PlayState* play = dynamic_cast<const PlayState*>(mGameState);
	const PauseState* pause = dynamic_cast<const PauseState*>(mGameState);
    if(menu) // HUVUDMENYN
    {
		//credit 
		/*if (e.key.keysym.sym == SDLK_c) // GÅ TILL CREDITS
		{
			menu->drawCred(mRenderer);
			SDL_Delay(5000); // show 5 second
		}*/
		
		if(e.type == SDL_MOUSEBUTTONDOWN) // SPELA KARTA
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );
			
			if (x > 512-100 && x < 512+100 && y > 200 && y < 400) //Klickområde STARTA SPELET
			{
				if (mPlayState == nullptr)
				{
					mPlayState = new PlayState;
					mPlayState->init();
				}
				changeState(mPlayState);

				if (Mix_PlayingMusic() == 0)
					Mix_PlayMusic(mMusic, 1);
			}
			if ( x > 512-100 && x < 512+100 && y > 450 && y < 650 ) // Klickområde AVSLUTA PROGRAMMET
				exit = true;
		} 
    }
    else if(play) // SPELET
    {
		// ENTER PAUSE MENU
		if(e.key.keysym.sym == SDLK_ESCAPE)
		{
			if ( mPauseState == nullptr )
			{
				mPauseState = new PauseState;
				mPauseState->init();
			}
			changeState(mPauseState);
		}
    }
    else if(pause) // PAUSEMENYN
    {
		if(e.key.keysym.sym == SDLK_UP) // GÅ TILLBAKA TILL SPELET
		{
			changeState(mPlayState);
		}
		else if (e.key.keysym.sym == SDLK_DOWN) // GÅ TILL MENYN OCH AVSLUTA NIVÅN
		{
			changeState(mMenuState);
			mPlayState->cleanup();
			mPlayState = nullptr; // Kan någon intyga att det destruerar mPlayStates PlayState korrekt?
		}
    }

    mGameState->handleEvent(e); //Övriga "Special" inputs för specifika states
    
}
