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
  Button(Vec2 pos, int width, int height, std::string str);
  ~Button();
  
  void draw(Renderer* renderer);
  bool mouseOver(Vec2 mousePos);

  
  SDL_Rect getRect();
  
private:
    Vec2 mPos;
    int mWidth, mHeight;
    std::string mFilePath;
    Texture* mTexture = nullptr;
    
};

#endif