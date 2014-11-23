#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Renderer.h"
#include "BaseState.h"
#include "Credit.h"
#include <iostream>

Game::Game()
{
    mRenderer = new Renderer;

    mActiveState = new MenuState;
    mActiveState->init();
}
 
Game::~Game()
{
    delete mActiveState;
}

bool Game::initWindow()
{
    // init the window using SDL
    return mRenderer->initSDL();
}

void Game::cleanup()
{
    ;
}
void Game::changeState(BaseState* state)
{
    // init the new state
    // using data from the previous state
    state->init(mActiveState->getNextStateData());

    // cleanup the old one(s)
    if(mActiveState != nullptr)
	delete mActiveState;
	
    mActiveState = state;
}

void Game::run()
{
    // TODO
    // make sure the game runs at 60 fps
    float dt = 0.0f;

    BaseState::StateId changeStateTo = mActiveState->changeStateTo();
    BaseState* newState = nullptr;
    if(changeStateTo == BaseState::PLAY_STATE)
		newState = new PlayState;
    else if(changeStateTo == BaseState::MENU_STATE)
		newState = new MenuState;
    else if(changeStateTo == BaseState::EDITOR_STATE)
		newState = new EditorState;
	else if (changeStateTo == BaseState::CREDIT)
		newState = new Credit;

    if(newState != nullptr)
	changeState(newState);
		
    // update the current gamestate
    mActiveState->update(dt);
	
    // all rendering should happen between beginScene() and endScene()
    mRenderer->beginScene();

    // draw the current gamestate
    mActiveState->draw(mRenderer);
	
    mRenderer->endScene();

}


void Game::handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_QUIT)
        exit = true;

    // update the current gamestate
    mActiveState->handleEvent(e, exit);
}
