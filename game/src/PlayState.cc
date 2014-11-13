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
	
}

void PlayState::init()
{
	mLevel = new Level("Maptest.txt");
	mPlayer = mLevel->findPlayer();
}

void PlayState::cleanup()
{
    delete mLevel;
    delete mPlayer;
    delete mTestBkgd;
}

void PlayState::update(float dt)
{
    mLevel->update(dt);
}

void PlayState::draw(Renderer* renderer)
{
    // draw test bkgd
    if(mTestBkgd != nullptr)
		renderer->drawTexture(Vec2(0, 0), 1024, 768, mTestBkgd);
    else
		mTestBkgd = renderer->loadTexture("../imgs/backgrounds/skygrad.jpg");

    mLevel->draw(renderer);
}

void PlayState::handleEvent(SDL_Event e)
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
	
}
