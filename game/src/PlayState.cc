#include "PlayState.h"
#include "Level.h"
#include "Renderer.h"
#include "Platform.h"
#include "Player.h"
#include "Object.h"
#include "Game.h"
#include "Enemy.h"


PlayState::PlayState()
{
    mTestBkgd = nullptr;
    mPlayer = nullptr;
    mPauseMenu = nullptr;
    mPaused = false;
	init();
}

PlayState::~PlayState()
{
    delete mLevel;
    delete mTestBkgd;
    delete mPauseMenu;
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
    if(!mPaused)
		mLevel->update(dt);
}

void PlayState::draw(Renderer* renderer)
{
    // draw test bkgd
    if(mTestBkgd != nullptr)
	renderer->drawTexture(Vec2(0, 0), mLevel->getLevelSize().x, mLevel->getLevelSize().y, mTestBkgd);
    else
	mTestBkgd = renderer->loadTexture("../imgs/backgrounds/skygrad.jpg");

	mLevel->draw(renderer);
	
    if(mPaused)
    {
	if (mPauseMenu != nullptr)
	    renderer->drawTextureScreen(Vec2(0,0), 1024, 768, mPauseMenu);
	else
	    mPauseMenu = renderer->loadTexture("../imgs/backgrounds/pause.png");
    }
}

void PlayState::handleEvent(SDL_Event e, bool& exit)
{
    if(!mPaused)
    {
		//If a key was pressed
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && !mPaused) 
		{
			//Adjust the velocity
			switch( e.key.keysym.sym )
			{
			case SDLK_SPACE:
			    if(!mPlayer->getjump() && !mPlayer->getfall())
			    {
					mPlayer->setjump(1); break;
			    }
			case SDLK_LEFT: mPlayer->addVel(-speed, 0); break;
			case SDLK_RIGHT: mPlayer->addVel(+speed, 0); break;
			}

			// ENTER PAUSE MENU
			if(e.key.keysym.sym == SDLK_ESCAPE)
				mPaused = !mPaused;
		}
		//If a key was released
		else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
		{
			//Adjust the velocity
			switch( e.key.keysym.sym )
			{
			case SDLK_LEFT: mPlayer->addVel(+speed, 0); break;
			case SDLK_RIGHT: mPlayer->addVel(-speed, 0); break;
			}
		}	
    }
    else
    {
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
		{
			if(e.key.keysym.sym == SDLK_ESCAPE) // GÅ TILLBAKA TILL SPELET
			{
				mPaused = !mPaused;
			}
			else if (e.key.keysym.sym == SDLK_DOWN) // GÅ TILL MENYN OCH AVSLUTA NIVÅN
			{
				setNextState(BaseState::MENU_STATE);
			}
		}
    }
    
}
