#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Vec2.h"

class Texture;

// handles all SDL code
class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool initSDL();

    void beginScene();
    void endScene();

    void drawTexture(Vec2 pos, int width, int height, Texture* texture);
    Texture* loadTexture(std::string filename);
    Texture* loadTexture(const char text[], unsigned int color1, unsigned int color2, unsigned int color3);
    int getScreenWidth(){ return SCREEN_WIDTH; }//bra att ha??
    int getScreenHeight(){ return SCREEN_HEIGHT; }
    // drawAnimation(...)
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font * mFont;
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;
    //SDL_Texture mTexture; ???
};

#endif