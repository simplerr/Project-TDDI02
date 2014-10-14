#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Object.h"
//#include "Event.h"

const int screenWidth = 600;
const int screenHeight = 400;
const int screenBPP = 32;



using namespace std;

bool init(SDL_Surface *& screen)
{
    
    
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
    screen = SDL_SetVideoMode( screenWidth, screenHeight, 0, 0 );
    
    /* set keyboard repeat */
    SDL_EnableKeyRepeat(70, 70);
    
    if ( screen == NULL )
        return false;
    
    SDL_WM_SetCaption( "Rockblock II", NULL);
    
    return true; 
}

void clean_up()
{
    SDL_Quit();
}

void HandleEvent(SDL_Event event, Player& player, bool& quit, int& jump)
{
    
    if(event.type == SDL_QUIT)
        quit = true;
    else if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
            quit = true;
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            player.setDir(false);
            player.setX(player.getX()+10);
            player.addFrame();
        }
        else if ( event.key.keysym.sym == SDLK_LEFT)
        {
            player.setDir(true);
            player.setX(player.getX()-10);
            player.addFrame();
        }
        else if (event.key.keysym.sym == SDLK_UP) // SDLK_DOWN:
	  {
	    if (player.getY() == screenHeight-50)
	      jump = 60;
	  }
    }
    else
        player.resFrame();
}

int main( int argc, char* args[] )
{
    bool quit = false;
    SDL_Surface* screen = NULL;
    int MAX_FPS = 60;
    int jump{};

    
    if ( !init(screen) )
    {
        return 1;
    }
    
    Objects sky{ 0, 0, "assets/sky.png", screen};
    //Objects tree{ 0, 0, "assets/tree.png", screen};
    
    Player player{200, 200, "assets/player/player-spritemap-v9-redpants.png", screen, "assets/player/player-spritemap-v9-redpantsH.png", 46, 50, 7};
    
    
    if ( SDL_Flip(screen) < 0 )
    {
        return 1;
    }
    
    while ( quit == false )
    {
        SDL_Event event;
        
        while( SDL_PollEvent( &event ) )
            HandleEvent(event, player, quit, jump);
        //else
        
        
        for ( int x = 0; x < screenWidth; x=x+400)
        {
            sky.setX(x);
            sky.render();
            for ( int y = 0; y < screenHeight; y=y+400)
            {
                sky.setY(y);
                sky.render();
            }
        }

        //tree.render();
        if (player.getX() <= 0)
            player.setX(0);
        else if(player.getX() >= screenWidth-50)
             player.setX(screenWidth-50);

        if (jump > 0 || player.getY() < screenHeight-50)
	  {
	    player.setFrame(7);
	    if(jump > 0)
	      {
		jump -= 2;
		player.setY(player.getY()-5);
	      }
	    else if (player.getY() < screenHeight-50)
	      player.setY(player.getY()+5);
	  }
        player.render();
        /* update the screen */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(1000/MAX_FPS);
        
    }


    clean_up();
    SDL_FreeSurface(screen);
    return 0;
}
