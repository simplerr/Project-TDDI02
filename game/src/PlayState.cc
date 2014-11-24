#include "PlayState.h"
#include "Level.h"
#include "Renderer.h"
#include "Platform.h"
#include "Player.h"
#include "Object.h"
#include "Game.h"
#include "Enemy.h"
#include <iostream>

PlayState::PlayState()
{
    mTestBkgd = nullptr;
    mPlayer = nullptr;
    mPauseMenu = nullptr;
	mLastTime = 0;
	mTimer = 0;
	boostSeconds = SPEEDBOOSTSEC;
    mPaused = false;
}

PlayState::~PlayState()
{
	for (unsigned int i = 0; i < buttonList.size(); i++)
		delete buttonList.at(i);

    delete mLevel;
    delete mTestBkgd;
    delete mPauseMenu;
}

void PlayState::init(string initData) // initData will be the filename of the level
{
    mLevel = new Level();
    mLevel->loadLevel(initData, 1); // 1 för att det är playstate
    mPlayer = mLevel->findPlayer();

	buttonList = {
		new ButtonImg(Vec2(350, 300), 300, 100, "../imgs/backgrounds/pauseback.png"),
		new ButtonImg(Vec2(350, 400), 300, 100, "../imgs/backgrounds/pausetomenu.png")
	};
}

void PlayState::cleanup()
{
    ;
}

void PlayState::update(float dt)
{
    if(!mPaused) {
		mLevel->update(dt);
		
		if (boostSeconds > 0) {
			mTimer = SDL_GetTicks();
			if (mTimer > mLastTime + 1000) {
				boostSeconds--;
				std::cout << boostSeconds << " xD\n";
				mLastTime = mTimer;
			}
		}

		
		if ( mPlayer->getPosition().x + mPlayer->getWidth() > mLevel->getLevelSize().x) { // Om spelaren klarat banan;
			if (getLvlUnlocks() == 0 && mLevel->getCurrentLevel() == FILEPATH_LVL1)
				incLvl();
			else if (getLvlUnlocks() == 1 && mLevel->getCurrentLevel() == FILEPATH_LVL2)
				incLvl();
			setNextState(BaseState::MENU_STATE);
			
		} 
		else if (mPlayer->getPosition().y + mPlayer->getHeight() > mLevel->getLevelSize().y || (!mLevel->getalive())) // Trillar spelaren ned, ladda om banan
		    init(mLevel->getCurrentLevel()); // (Kan behövas ändras)
	}
}

void PlayState::draw(Renderer* renderer)
{
    /* draw test bkgd
    if(mTestBkgd != nullptr)
		renderer->drawTexture(Vec2(0, 0), mLevel->getLevelSize().x, mLevel->getLevelSize().y, mTestBkgd);
    else
	mTestBkgd = renderer->loadTexture("../imgs/backgrounds/skygrad.jpg"); */

	mLevel->draw(renderer);
	
	if (mPaused) {
		for (unsigned int i = 0; i < buttonList.size(); i++)
			buttonList.at(i)->draw(renderer);
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
					mPlayer->setjump(1); 
			    }
			break;
			case SDLK_LEFT: mPlayer->addVel(-speed, 0); break;
			case SDLK_RIGHT: mPlayer->addVel(+speed, 0); break;
			default: break;
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
			default: break;
			}
		}	
    }
    else
    {
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
			if(e.key.keysym.sym == SDLK_ESCAPE) // GÅ TILLBAKA TILL SPELET VIA ESCAPE
				mPaused = !mPaused;

		if(e.type == SDL_MOUSEBUTTONDOWN) // Kolla musknappnedtryck
		{
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			for (unsigned int i = 0; i < buttonList.size(); i++) {
			
				if (buttonList.at(i)->mouseOver(mousePos)) {

					switch (i) {
					case 0:
						mPaused = !mPaused;
						break;
					case 1:
						setNextState(BaseState::MENU_STATE);
						break;
					default:
						break;
					}

				}

			}

		}

	}
    
}


void PlayState::setSpeed(float s)
{
	speed = s;
}

float PlayState::getSpeed()
{
	return speed;
}

void PlayState::setTimer(Uint32 t)
{
	mTimer = t;
}

Uint32 PlayState::getTimer()
{
	return mTimer;
}
