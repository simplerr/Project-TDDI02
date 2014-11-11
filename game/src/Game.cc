#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
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
    
    const MenuState* ms = dynamic_cast<const MenuState*>(mGameState);
    if(ms)
    {
	if(e.key.keysym.sym == SDLK_KP_ENTER)
	    changeState(new PlayState);
    }
    
    const PlayState* ps = dynamic_cast<const PlayState*>(mGameState);
    if(ps)
    {
	if(e.key.keysym.sym == SDLK_ESCAPE)
	    changeState(new MenuState);
    }
    
    mGameState->handleEvent(e);
    
}
