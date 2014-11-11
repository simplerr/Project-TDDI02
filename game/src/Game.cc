#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Renderer.h"
#include "BaseState.h"

Game::Game()
{
    mRenderer = new Renderer;
    mGameState = nullptr;
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
    if(mGameState != nullptr)
    {
	mGameState->cleanup();
    }

    // init the new one
    mGameState = state;
    mGameState->init();
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
    
    //const MenuState* ms = dynamic_cast<const MenuState*>(mGameState);
	MenuState* ms = dynamic_cast<MenuState*>(mGameState);
    if(ms)
    {
<<<<<<< HEAD
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
	    //Get mouse position
	    int x, y;
	    SDL_GetMouseState( &x, &y );
	    if (x > 200 && x < 400 && y > 200 && y < 400) //Ska inte hårdkodas
	    {
		changeState(new PlayState);
	    }
	}   
=======
		//credit 
		if (e.key.keysym.sym == SDLK_c) {
			ms->drawCred(mRenderer);
			SDL_Delay(1000); // show 5 second
		}

		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );
			if (x > 200 && x < 400 && y > 200 && y < 400)
			{
				changeState(new PlayState);
			}
	
		}   
>>>>>>> 1a871e93608a0a60869917e9b901c43beb0ec83f
    }
    
    const PlayState* ps = dynamic_cast<const PlayState*>(mGameState);
    if(ps)
    {
		if(e.key.keysym.sym == SDLK_ESCAPE)
			changeState(new PauseState);
    }
    
	const PauseState* pas = dynamic_cast<const PauseState*>(mGameState);
    if(pas)
    {
		if(e.key.keysym.sym == SDLK_DOWN)
			changeState(new PlayState);
		else if (e.key.keysym.sym == SDLK_UP)
			changeState(new MenuState);
    }

    mGameState->handleEvent(e);
    
}
