
#include <unistd.h>
#include <cstdlib>
#include "Sound.hpp"

int main()
{
  AudioManager	audioManager(10);
  //  MusicManager	music("test.ogg");
  SoundManager*  poney = new SoundManager("test.wav");
  int i = 0;

  // music.play(-1);
  // music.volume(MIX_MAX_VOLUME);


  while (i < 10)
    {
      i++;
      poney->play(0);
      sleep(1);
    }
  return 0;
}
