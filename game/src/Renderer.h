#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Vec2.h"
#include "Texture.h"

// handles all SDL code
class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    bool initSDL();

    void beginScene();
    void endScene();

    void drawTexture(Vec2 pos, int width, int height, Texture* texture, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTextureScreen(Vec2 pos, int width, int height, Texture* texture, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    Texture* loadTexture(std::string filename);
    Texture* loadTexture(string text, unsigned int color1, unsigned int color2, unsigned int color3);
    void updateCamera(int x, int y, int width, int height, int, int);
    Vec2 getCameraAdjustment();
    //int getLEVEL_WIDTH(){ return LEVEL_WIDTH; }//bra att ha??
    //int getLEVEL_HEIGHT(){ return LEVEL_HEIGHT; }
    //void setLEVEL_WIDTH(int newLW){ LEVEL_WIDTH=newLW; }//bra att ha??
    //void setLEVEL_HEIGHT(int newLH){ LEVEL_HEIGHT=newLH; }
    // drawAnimation(...)
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font * mFont;
    SDL_Rect camera;
    
};

#endif