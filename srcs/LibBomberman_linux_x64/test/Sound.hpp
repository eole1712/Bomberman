
#ifndef SOUND_H_
# define SOUND_H_

#include <exception>
#include <SDL/SDL_mixer.h>

class AudioManager
{
public:
  AudioManager();
  ~AudioManager();
private:
};

class MusicManager
{
public:
  MusicManager(char *file);
  ~MusicManager();

  void		play(int loop);
  static void	pause();
  static void	resume();
  static void	rewind();
  static void	volume();
private:
  MusicManager();
  Mix_Music*	_music;
};

#endif /* !SOUND_H_ */
