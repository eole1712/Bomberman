
#ifndef SOUND_H_
# define SOUND_H_

#include <string>
#include <vlc/vlc.h>

class AudioManager
{
public:
  AudioManager();
  ~AudioManager();

  libvlc_instance_t*	getInst() const;
private:
  libvlc_instance_t*	_inst;
};

class SoundManager
{
public:
  SoundManager(AudioManager*, const std::string& file);
  ~SoundManager();

  void		play() const;
  bool		isPlaying() const;
private:
  SoundManager();
  libvlc_media_t*		_media;
  libvlc_media_player_t*	_mediaPlayer;
};

#endif /* !SOUND_H_ */
