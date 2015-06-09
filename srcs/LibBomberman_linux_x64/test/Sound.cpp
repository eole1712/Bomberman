
#include "Sound.hpp"

AudioManager::AudioManager()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
      throw new std::exception;
    }
}

AudioManager::~AudioManager()
{
  Mix_CloseAudio();
}

MusicManager::MusicManager(char *file)
{
  _music = Mix_LoadMUS(file);
}

MusicManager::~MusicManager()
{
  Mix_FreeMusic(_music);
}

void		MusicManager::play(int loop)
{
  Mix_PlayMusic(_music, loop);
}

void	MusicManager::pause()
{
  Mix_PauseMusic();
}

void	MusicManager::resume()
{
  Mix_ResumeMusic();
}

void	MusicManager::rewind()
{
  Mix_RewindMusic();
}

void	MusicManager::volume(int vol)
{
  Mix_VolumeMusic(vol);
}
