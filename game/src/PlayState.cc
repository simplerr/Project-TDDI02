#include "PlayState.h"
#include "Level.h"
#include "Renderer.h"
#include "Platform.h"
#include "Player.h"
#include "Object.h"

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
    mLevel = new Level("test.txt");

    mLevel->addObject(new Platform(Vec2(100, 600), 100, 100, "../imgs/platform.jpg"));
    mLevel->addObject(new Platform(Vec2(400, 500), 200, 100, "../imgs/platform.jpg"));
    mLevel->addObject(new Platform(Vec2(900, 620), 100, 200, "../imgs/platform.jpg"));
    
    mPlayer = mLevel->addPlayer(500, 400);
}

void PlayState::cleanup()
{
    delete mLevel;
}

void PlayState::update(float dt)
{
    mLevel->update(dt);

    // Player movement test
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    float speed = 2.0f;
    if( currentKeyStates[ SDL_SCANCODE_UP ] &&  currentKeyStates[ SDL_SCANCODE_RIGHT ])
    {
            
    }
    else if( currentKeyStates[ SDL_SCANCODE_UP ] &&  currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
           
    }
    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
	mPlayer->setPosition(mPlayer->getPosition().x - speed, mPlayer->getPosition().y);
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
	mPlayer->setPosition(mPlayer->getPosition().x + speed, mPlayer->getPosition().y);
    }
    else if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
	
    }
}

void PlayState::draw(Renderer* renderer)
{
    // draw test bkgd
    if(mTestBkgd != nullptr)
	renderer->drawTexture(Vec2(0, 0), 1024, 768, mTestBkgd);
    else
	mTestBkgd = renderer->loadTexture("../imgs/skygrad.jpg");

    mLevel->draw(renderer);
}
