#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Renderer.h"
#include "Texture.h"
#include "Vec2.h"
using namespace std;

Renderer::Renderer()
{
    mRenderer = nullptr;
    mWindow = nullptr;
}

Renderer::~Renderer()
{
    // cleanup SDL
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;
    SDL_Quit();
}

bool Renderer::initSDL()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	cerr << "ERROR: Kunde inte initiera SDL\n";
        success = false;
    }
    else
    {

	 // create window
        mWindow = SDL_CreateWindow("Rockblock II", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(mWindow == NULL)
        {
            cerr << "ERROR: Kunde inte skapa fönster\n";
            success = false;;
        }else
        {
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED );
            if(mRenderer == NULL)
            {
                cerr << "ERROR: Kunde inte skapa renderer\n" << SDL_GetError();
		success = false;
            }else
            {
                // initialize renderer color
                SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
				// initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
				{ 
					cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl; 
					success = false; 
				}

                // initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

void Renderer::beginScene()
{
    SDL_RenderClear(mRenderer);
}

void Renderer::endScene()
{
     SDL_RenderPresent(mRenderer);
     SDL_Delay(1000/60); // 60 FPS
}

void Renderer::drawTexture(Vec2 pos, int width, int height, Texture* texture)
{
    SDL_Rect SDLRect{pos.x, pos.y, width, height};


    SDL_RenderCopy(mRenderer, texture->getData(), nullptr, &SDLRect);
}

Texture* Renderer::loadTexture(std::string filename)
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* tmpSurface = IMG_Load(filename.c_str() );
    if(tmpSurface == NULL)
    {
        cerr << "ERROR: Kunde inte öppna fil: " << filename << IMG_GetError() << endl;
    }else
    {
        //Convertera surface till screen format
        newTexture = SDL_CreateTextureFromSurface(mRenderer, tmpSurface);
        if(newTexture == NULL)
        {
            cerr << "ERROR: Misslyckades konvertera fil: " << filename << SDL_GetError() << endl;
        }
        SDL_FreeSurface(tmpSurface);
    }

    return new Texture(newTexture);
}
