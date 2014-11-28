#include "Button.h"
#include <iostream>

Button::Button(Vec2 pos, int width, int height)
  : mPos(pos), mWidth(width), mHeight(height)
{}

Button::~Button()
{
    //delete mTexture;
}

void Button::draw(Renderer* renderer, std::string newString)
{
    ;
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


ButtonText::ButtonText(Vec2 pos, int width, int height, const std::string str, const  int color1, const int color2, const int color3)
: Button(pos, width, height), mFilePath(str), mcolor1(color1), mcolor2(color2), mcolor3(color3)
{
    
}

ButtonText::~ButtonText()
{
    delete mText;
}

void ButtonText::draw(Renderer* renderer, std::string newString)
{
    SDL_Rect rect = getRect();
    if(mText != nullptr)
    {
        if (newString != ""){
            delete mText;
            mText = renderer->loadTexture(newString, mcolor1, mcolor2, mcolor3);
        }
        if (getHighlightOn())
        {
            renderer->drawTextureScreen(Vec2(rect.x, rect.y), rect.w, rect.h, mHighlight);
            setHighlightOn();
        }
        renderer->drawTextureScreen(Vec2(rect.x, rect.y), rect.w, rect.h, mText);
    }
    else
    {
        mText = renderer->loadTexture(mFilePath, mcolor1, mcolor2, mcolor3);
        mHighlight = renderer->loadTexture("../imgs/highlight.png");
    }
}


ButtonImg::ButtonImg(Vec2 pos, int width, int height, std::string str)
  : Button(pos, width, height), mFilePath(str)
{}

ButtonImg::~ButtonImg()
{
    delete mTexture;
}

void ButtonImg::draw(Renderer* renderer, std::string newString)
{
    SDL_Rect rect = getRect();
    if(mTexture != nullptr)
      renderer->drawTextureScreen(Vec2(rect.x, rect.y), rect.w, rect.h, mTexture);
    else
      mTexture = renderer->loadTexture(mFilePath);
}