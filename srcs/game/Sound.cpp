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

SoundManager::SoundManager(AudioManager* inst, const std::string& file)
{
  this->_media = libvlc_media_new_path(inst->getInst(), file.c_str());
  this->_mediaPlayer = libvlc_media_player_new_from_media(this->_media);
  libvlc_media_release(this->_media);
}

SoundManager::~SoundManager()
{
  libvlc_media_player_stop(this->_mediaPlayer);
  libvlc_media_player_release(this->_mediaPlayer);
}

void		SoundManager::play()
{
  libvlc_media_player_play(this->_mediaPlayer);
}

/* !SOUND MANAGER */
