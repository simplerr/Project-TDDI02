#include "Sound.h"

Sound::Sound(const char *str)
{
	mMusic = Mix_LoadMUS(str);
}

Sound::~Sound()
{
	;
}

void Sound::play()
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(mMusic, 1);
}

void Sound::pause()
{
	if (Mix_PausedMusic() != 0)
		Mix_PauseMusic();

	if (Mix_PlayingMusic() == 0)
		Mix_PauseMusic();
}
