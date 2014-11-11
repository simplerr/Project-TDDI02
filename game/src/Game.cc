#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Renderer.h"
#include "BaseState.h"

Game::Game()
{
    mRenderer = new Renderer;
	
    mGameState = new MenuState;
	mGameState->init();
	mPlayState = new PlayState;
	mPlayState->init();
	mMenuState = new MenuState;
	mMenuState->init();
	mPauseState = new PauseState;
	mPauseState->init();
}
 
Game::~Game()
{
  //delete mGameState;
    delete mRenderer;
}

bool Game::initWindow()
{
    // init the window using SDL
   return mRenderer->initSDL();
}

void Game::changeState(BaseState* state)
{
    // cleanup the old one
    /*if(mGameState != nullptr)
    {
		mGameState->cleanup();
    }*/

    // init the new one
    mGameState = state;
    //mGameState->init();
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

    // draw the current gamestate
	mPlayState->draw(mRenderer);
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
		
	MenuState* menu = dynamic_cast<MenuState*>(mGameState);
	const PlayState* play = dynamic_cast<const PlayState*>(mGameState);
	const PauseState* pause = dynamic_cast<const PauseState*>(mGameState);
    if(menu)
    {
		//credit 
		if (e.key.keysym.sym == SDLK_c)
		{
			menu->drawCred(mRenderer);
			SDL_Delay(5000); // show 5 second
		}

		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );
			
			if (x > 200 && x < 400 && y > 200 && y < 400) //Klickområde
			{
				changeState(mPlayState);
			}
	
		} 

    }
    else if(play)
    {
		if(e.key.keysym.sym == SDLK_ESCAPE)
		{
			changeState(mPauseState);
		}
    }
    else if(pause)
    {
		if(e.key.keysym.sym == SDLK_UP)
		{
			changeState(mPlayState);
		}
		else if (e.key.keysym.sym == SDLK_DOWN)
		{
			changeState(mMenuState);
		}
    }

    mGameState->handleEvent(e);
    
}
