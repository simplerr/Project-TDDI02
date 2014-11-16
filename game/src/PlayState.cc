#include "PlayState.h"
#include "Level.h"
#include "Renderer.h"
#include "Platform.h"
#include "Player.h"
#include "Object.h"
#include "Game.h"


PlayState::PlayState()
{
    mTestBkgd = nullptr;
    mPlayer = nullptr;
}

PlayState::~PlayState()
{
	delete mLevel;
    delete mPlayer;
    delete mTestBkgd;
}

void PlayState::init()
{
	mLevel = new Level();
	mLevel->loadLevel("Maptest2.txt");
	mPlayer = mLevel->findPlayer();
}

void PlayState::cleanup()
{
    ;
}

void PlayState::update(float dt)
{
	mLevel->update(dt);
	
	Mix_Music *mMusic = Mix_LoadMUS("../sounds/Hits_from_the_bong.mp3");
	if (mMusic)
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(mMusic, 1);
}

void PlayState::draw(Renderer* renderer)
{
	renderer->updateCamera(mPlayer->getPosition().x, mPlayer->getPosition().y, mPlayer->getWidth(), mPlayer->getHeight());
    // draw test bkgd
    if(mTestBkgd != nullptr)
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mTestBkgd);
    else
		mTestBkgd = renderer->loadTexture("../imgs/backgrounds/skygrad.jpg");

    mLevel->draw(renderer);
}

void PlayState::handleEvent(SDL_Event e, bool& exit)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
	case SDLK_UP: mPlayer->addVel(0, -speed); break; // case SDLK_UP: mPlayer->playerJump(speed); break;
	case SDLK_DOWN: mPlayer->addVel(0, +speed); break;
	case SDLK_LEFT: mPlayer->addVel(-speed, 0); break;
	case SDLK_RIGHT: mPlayer->addVel(+speed, 0); break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
	case SDLK_UP: mPlayer->addVel(0, +speed); break; // case SDLK_UP: mPlayer->playerJump(speed); break;
	case SDLK_DOWN: mPlayer->addVel(0, -speed); break;
	case SDLK_LEFT: mPlayer->addVel(+speed, 0); break;
	case SDLK_RIGHT: mPlayer->addVel(-speed, 0); break;
        }
    }
	
    // ENTER PAUSE MENU
    if(e.key.keysym.sym == SDLK_ESCAPE)
    {
	setNextState(BaseState::PAUSE_STATE);
    }
}
