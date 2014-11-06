#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
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

    // drawAnimation(...)
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};

#endif