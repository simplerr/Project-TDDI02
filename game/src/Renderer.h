#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Vec2.h"
#include "Texture.h"

static const int SCREEN_WIDTH = 1024;
static const int SCREEN_HEIGHT = 768;
static int LEVEL_WIDTH; // dom skall inte vara static men åtkomst överallt
static int LEVEL_HEIGHT;

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
    void drawPlayer(Vec2 pos, int width, int height, Texture* texture, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    Texture* loadTexture(std::string filename);
    Texture* loadTexture(const char text[], unsigned int color1, unsigned int color2, unsigned int color3);
    void updateCamera(int x, int y, int width = 0, int height = 0);
    
    int getScreenWidth(){ return SCREEN_WIDTH; }//bra att ha??
    int getScreenHeight(){ return SCREEN_HEIGHT; }
    int getLevelWidth(){ return LEVEL_WIDTH; }//bra att ha??
    int getLevelHeight(){ return LEVEL_HEIGHT; }
    // drawAnimation(...)
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font * mFont;
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
};

#endif