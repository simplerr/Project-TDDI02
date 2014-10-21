#include "PlayState.h"
#include "Level.h"

PlayState::PlayState()
{

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

    mLevel->draw(renderer);
}
