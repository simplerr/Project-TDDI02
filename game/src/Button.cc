#include "Button.h"
#include <iostream>

Button::Button(Vec2 pos, int width, int height, std::string str)
  : mPos(pos), mWidth(width), mHeight(height), mFilePath(str)
{}

Button::~Button()
{
    delete mTexture;
}

void Button::draw(Renderer* renderer)
{
    if(mTexture != nullptr)
      renderer->drawTexture(mPos, mWidth, mHeight, mTexture);
    else
      mTexture = renderer->loadTexture(mFilePath);
}

bool Button::mouseOver(Vec2 mousePos)
{
    return ( mousePos.x > mPos.x && mousePos.y > mPos.y && mousePos.x < mPos.x + mWidth && mousePos.y < mPos.y + mHeight );
}

SDL_Rect Button::getRect()
{
  SDL_Rect rect;
  rect.x = mPos.x;
  rect.y = mPos.y;
  rect.w = mWidth;
  rect.h = mHeight;
  return rect;
}