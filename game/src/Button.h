#ifndef BUTTON_H
#define BUTTON_H

#include "Vec2.h"
#include "Texture.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <string>

class Button
{
public:
  Button(Vec2 pos, int width, int height);
  //Button(Vec2 pos, int width, int height, std::string str);
  virtual ~Button();
  
  virtual void draw(Renderer* renderer);
  bool mouseOver(Vec2 mousePos);

  
  SDL_Rect getRect();
  
private:
    Vec2 mPos;
    int mWidth, mHeight;
};
  
class ButtonText : public Button
{
public:
    ButtonText(Vec2 pos, int width, int height, std::string str, const int color1, const int color2, const int color3);
    ~ButtonText();
    
    void draw(Renderer* renderer);
private:
    const int mcolor1, mcolor2, mcolor3;
    Texture* mText = nullptr;
    std::string mFilePath;
};

class ButtonImg : public Button
{
public:
    ButtonImg(Vec2 pos, int width, int height, std::string str);
    ~ButtonImg();
    
    void draw(Renderer* renderer);
private:
    Texture* mTexture = nullptr;
    std::string mFilePath;
};

#endif