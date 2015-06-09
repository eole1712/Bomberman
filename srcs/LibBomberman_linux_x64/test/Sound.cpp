
#include <iostream>
#include "Sound.hpp"

/* AUDIOMANAGER */

AudioManager::AudioManager(int nbChannels)
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
      throw new std::exception;
    }
  Mix_AllocateChannels(nbChannels);
}

AudioManager::~AudioManager()
{
  Mix_CloseAudio();
}

/* !AUDIOMANAGER */
/* MUSIC MANAGER */

MusicManager::MusicManager(const std::string& file)
{
  _music = Mix_LoadMUS(file.c_str());


  std::cout << Mix_GetError() << std::endl;
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

/* !MUSIC MANAGER */
/* SOUND MANAGER */

SoundManager::SoundManager(const std::string& file)
{
  _sound = Mix_LoadWAV(file.c_str());
}

SoundManager::~SoundManager()
{
  Mix_FreeChunk(_sound);
}

void	SoundManager::play(int loop)
{
  Mix_PlayChannel(-1, _sound, loop);
}

/* !SOUND MANAGER */
