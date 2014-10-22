#include <SDL2/SDL.h>
#include "Game.h"
#include "PlayState.h"
#include <iostream>

void handleEvent(SDL_Event e, bool& exit)
{
    if(e.type == SDL_QUIT)
        exit = true;
}

int main(int argc, char* argv[])
{
    Game* game = new Game;

    if(!game->initWindow())
    {
	std::cerr << "Game::initWindow() failed" << std::endl;
	return 1;
    }

    game->changeState(new PlayState);

    // while(1)
    bool exit = false;

    while(!exit)
    {
	SDL_Event e;

	// poll SDL event
	while(SDL_PollEvent(&e) != 0)	
	    handleEvent(e, exit);

	game->run();
    }
   

    return 0;
}
