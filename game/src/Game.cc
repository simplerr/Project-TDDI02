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
    delete mPlayState;
    delete mMenuState;
    delete mPauseState;
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
	mMenuState->cleanup();
	mPauseState->cleanup();
	
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
	if(mGameState->getStateId() == BaseState::PAUSE_STATE)
		mPlayState->draw(mRenderer);
	// #########################
	
	// draw the current gamestate
	mGameState->draw(mRenderer);
	
    mRenderer->endScene();
}


void Game::handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_QUIT)
        exit = true;

    BaseState::StateId changeStateTo = mGameState->changeStateTo();

    if(changeStateTo == BaseState::PLAY_STATE)
    {
	mPlayState = new PlayState;
	mPlayState->init();
	changeState(mPlayState);         	
    }
    else if(changeStateTo == BaseState::MENU_STATE)
    {
	mMenuState = new MenuState;
	mMenuState->init();
	changeState(mMenuState);
    }
    else if(changeStateTo == BaseState::PAUSE_STATE)
    {
	mPauseState = new PauseState;
	mPauseState->init();
	changeState(mPauseState);
    }
    else if(changeStateTo == BaseState::EDITOR_STATE)
    {
	//mEditorState = new EditorState;
	//mEditorState->init();
	//changeState(mPauseState);
    }

    mGameState->handleEvent(e, exit); //Övriga "Special" inputs för specifika states
}
