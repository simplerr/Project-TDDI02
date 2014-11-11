#include "Game.h"
#include "PlayState.h"
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
	//delete mGameState;
	//mRenderer = new Renderer;;
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
    if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
        exit = true;
	
    if(e.key.keysym.sym == SDLK_KP_ENTER)
        changeState(new PlayState);
	
    mGameState->handleEvent(e);
    
    /*const PlayState* ps = dynamic_cast<const PlayState*>(mGameState);
    
    if(ps)
    {
	ps->draw(mRenderer, e);
    } */
    
}
