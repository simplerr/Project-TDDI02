#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

class Sound {
 public:
	Sound(const char *);
	~Sound();

	void play();
	void pause();

 private:
	Mix_Music *mMusic;
};

#endif
