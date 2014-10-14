#include <SDL2/SDL.h>
#include "Object.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 400;
    
bool init(SDL_Window*& window, SDL_Renderer*& renderer)
{
    bool success{true};

    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "ERROR: Kunde inte initiera SDL\n";
        success = false;
    }else
    {
        //Skapa fönster
        window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            cerr << "ERROR: Kunde inte skapa fönster\n";
            success = false;
        }else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if(renderer == NULL)
            {
                cerr << "ERROR: Kunde inte skapa renderer\n" << SDL_GetError();
                success = false;
            }else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                //Initialize PNG loading
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

void close(SDL_Window*& window, SDL_Renderer*& renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_QUIT;
}
void handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_QUIT)
        exit = true;
}

int main(int argc, char* argv[])
{
    
    bool exit{false};
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //The surface contained by the window
    SDL_Renderer* renderer = NULL;
    
    if (!init(window, renderer))
    {
        cerr << "ERROR: Initieringen misslyckades\n";
        return 1;
    }else
    {
        Object sky{0,0,600,400,renderer,"images/sky.png"};
        Player player(50,50,46,50,renderer,"images/player/player-spritemap-v9-redpants.png", "images/player/player-spritemap-v9-redpantsH.png");
        Object box(100,170, 100, 50, renderer,"images/block.png");
        Object box2(400,170, 100, 50, renderer,"images/block.png");
        vector<Object> collissionObjects;
        collissionObjects.push_back(box);
        collissionObjects.push_back(box2);
        
        while(!exit)
        {
            SDL_Event e;
            while(SDL_PollEvent(&e) != 0)
            {
                handleEvent(e, exit);
            }
            
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            
            if( currentKeyStates[ SDL_SCANCODE_UP ] &&  currentKeyStates[ SDL_SCANCODE_RIGHT ])
            {
                     player.moveRight();
                     player.moveUp();
            }
            else if( currentKeyStates[ SDL_SCANCODE_UP ] &&  currentKeyStates[ SDL_SCANCODE_LEFT ] )
            {
                    player.moveLeft();
                    player.moveUp();
            }
            else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
            {
                    player.moveLeft();
            }
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
            {
                    player.moveRight();
            }
            else if( currentKeyStates[ SDL_SCANCODE_UP ] )
            {
                    player.moveUp();
            }else
                player.moveStand();
            

            
            SDL_RenderClear(renderer);
            //Clear screen
            sky.render();
            //player.Collision(box2);
            for (int i{}; i < collissionObjects.size(); ++i)
            {
                collissionObjects[i].render();
            }
            player.render();
            if (!(player.Collision(collissionObjects)))
            {
                player.setY(player.getY()+2);
            }
           
           
           
           /* if (player.getY() > SCREEN_HEIGHT-50)
            {
               player.setY(SCREEN_HEIGHT-50);
            }else
            {
                player.setY(player.getY()+2);
            }*/
            //Update screen
            SDL_RenderPresent( renderer );
            SDL_Delay(1000/60);

        }
    }
    
    close(window, renderer);
}