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
	else if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}

void Sound::pause()
{
		Mix_PauseMusic();
}
