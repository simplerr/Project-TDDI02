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
  Button(Vec2 pos, int width, int height, std::string str);
  Button(Vec2 pos, int width, int height, std::string str, int color1, int color2, int color3);
  ~Button();
  
  void draw(Renderer* renderer);
  bool mouseOver(Vec2 mousePos);

  
  SDL_Rect getRect();
  
private:
    Vec2 mPos;
    int mWidth, mHeight;
    std::string mFilePath;
    Texture* mTexture = nullptr;
    int mcolor1, mcolor2, mcolor3;
};
  /* 
class MenuItem : public Interface
{
    MenuItem(Vec2 pos, int width, int height, std::string str)
};

class Button : public Interface
{
    MenuItem(Vec2 pos, int width, int height, std::string str)
;}
*/
  
class TextItem : public Button
{
public:
    TextItem(Vec2 pos, int width, int height, std::string str, const int color1, const int color2, const int color3);
    ~TextItem();
    
    void draw(Renderer* renderer);
private:
    const int mcolor1, mcolor2, mcolor3;
    Texture* mText = nullptr;
    std::string FilePath;
};

#endif