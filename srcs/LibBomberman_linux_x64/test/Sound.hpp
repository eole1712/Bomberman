
#ifndef SOUND_H_
# define SOUND_H_

#include <string>
#include <exception>
#include <SDL/SDL_mixer.h>

class AudioManager
{
public:
  AudioManager(int nbChannels);
  ~AudioManager();
private:
};

class MusicManager
{
public:
  MusicManager(const std::string& file);
  ~MusicManager();

  void		play(int loop);
  static void	pause();
  static void	resume();
  static void	rewind();
  static void	volume(int vol);
private:
  MusicManager();
  Mix_Music*	_music;
};

class SoundManager
{
public:
  SoundManager(const std::string& file);
  ~SoundManager();

  void		play(int loop);
private:
  SoundManager();
  Mix_Chunk*	_sound;
};

#endif /* !SOUND_H_ */
