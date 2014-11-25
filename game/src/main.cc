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

    bool exit = false, mute = false;
	Sound s("../sounds/Hyperfun.mp3");
    while(!exit)
    {
		if (!mute)
			s.play();
		else
			s.pause();
		
		SDL_Event e;

		// poll SDL event
		while(SDL_PollEvent(&e) != 0)	
			game->handleEvent(e, exit);

		game->run();

		mute = game->getMute();
    }
	
   //game->cleanup();
   delete game;

    return 0;
}
