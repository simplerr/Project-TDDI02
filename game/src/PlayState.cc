#include "PlayState.h"
#include "Level.h"
#include "Renderer.h"

PlayState::PlayState()
{
    mTestBkgd = nullptr;
}

PlayState::~PlayState()
{

}

void PlayState::init()
{
    mLevel = new Level("test.txt");
}

void PlayState::cleanup()
{
    delete mLevel;
}

void PlayState::update(float dt)
{
    mLevel->update(dt);
}

void PlayState::draw(Renderer* renderer)
{
    // draw test bkgd
    if(mTestBkgd != nullptr)
	renderer->drawTexture(Vec2(0, 0), 640, 480, mTestBkgd);
    else
	mTestBkgd = renderer->loadTexture("../imgs/skygrad.jpg");

    mLevel->draw(renderer);
}
