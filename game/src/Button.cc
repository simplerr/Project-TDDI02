#include "Button.h"
#include <iostream>

Button::Button(Vec2 pos, int width, int height)
  : mPos(pos), mWidth(width), mHeight(height)
{}

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
      renderer->drawTextureScreen(mPos, mWidth, mHeight, mTexture);
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


TextItem::TextItem(Vec2 pos, int width, int height, std::string str,const  int color1, const int color2, const int color3)
: Button(pos, width, height), FilePath(str), mcolor1(color1), mcolor2(color2), mcolor3(color3)
{}

void TextItem::draw(Renderer* renderer)
{
    std::cout << "sdddddddsd";
    SDL_Rect rect = getRect();
    if(mText != nullptr){
         std::cout << "sdddddddsd";
        renderer->drawTextureScreen(Vec2(rect.x, rect.y), rect.w, rect.h, mText);
       std::cout << "sdddddddsd";}
    else{
        std::cout << "sdsd";
        mText = renderer->loadTexture(FilePath, mcolor1, mcolor2, mcolor3);
    }
}