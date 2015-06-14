#include <iostream>
#include <vlc/vlc.h>
#include "Sound.hpp"

/* AUDIOMANAGER */
AudioManager::AudioManager()
{
  this->_inst = libvlc_new(0, NULL);
}

AudioManager::~AudioManager()
{
  libvlc_release(this->_inst);
}

libvlc_instance_t*	AudioManager::getInst() const
{
  return (this->_inst);
}
/* !AUDIOMANAGER */

/* SOUND MANAGER */
SoundManager::SoundManager(AudioManager* audioManager, const std::string& file)
{
  if (file != "")
    {
      this->_media = libvlc_media_new_path(audioManager->getInst(), file.c_str());
      this->_mediaPlayer = libvlc_media_player_new_from_media(this->_media);
      libvlc_media_release(this->_media);
    }
  else
    this->_mediaPlayer = NULL;
}

SoundManager::~SoundManager()
{
  if (this->_mediaPlayer != NULL)
    {
      libvlc_media_player_stop(this->_mediaPlayer);
      libvlc_media_player_release(this->_mediaPlayer);
    }
}

void	SoundManager::play() const
{
  if (this->_mediaPlayer != NULL)
    libvlc_media_player_play(this->_mediaPlayer);
}

bool	SoundManager::isPlaying() const
{
  return (this->_mediaPlayer != NULL && libvlc_media_player_is_playing(this->_mediaPlayer));
}
/* !SOUND MANAGER */
