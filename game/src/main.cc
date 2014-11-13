#include <SDL2/SDL.h>
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include <iostream>


int main(int argc, char* argv[])
{
    Game* game = new Game;

    if(!game->initWindow())
    {
	std::cerr << "Game::initWindow() failed" << std::endl;
	return 1;
    }

    bool exit = false;

    while(!exit)
    {
		SDL_Event e;

		// poll SDL event
		while(SDL_PollEvent(&e) != 0)	
			game->handleEvent(e, exit);

		game->run();
    }
	
   game->cleanup();

    return 0;
}
