#include "PlayState.h"
#include "Level.h"
#include "Renderer.h"
#include "Platform.h"

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

    mLevel->addObject(new Platform(Vec2(100, 100), 100, 100, "../imgs/platform.jpg"));
    mLevel->addObject(new Platform(Vec2(400, 100), 200, 100, "../imgs/platform.jpg"));
    mLevel->addObject(new Platform(Vec2(200, 300), 100, 200, "../imgs/platform.jpg"));
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
	renderer->drawTexture(Vec2(0, 0), 1024, 768, mTestBkgd);
    else
	mTestBkgd = renderer->loadTexture("../imgs/skygrad.jpg");

    mLevel->draw(renderer);
}
