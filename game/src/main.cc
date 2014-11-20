#include <SDL2/SDL.h>
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "Sound.h"
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
	Sound s("../sounds/music.mp3");
    while(!exit)
    {
		s.play();
		SDL_Event e;

		// poll SDL event
		while(SDL_PollEvent(&e) != 0)	
			game->handleEvent(e, exit);

		game->run();
    }
	
   //game->cleanup();
   delete game;

    return 0;
}
