#include <iostream>
#include "Core.hpp"

void			showfps()
{
  static unsigned int	lasttime = 0;
  static unsigned int	nbframe = 0;
  unsigned int		curtime;
  unsigned int		fps;
  static unsigned int	maxfps = 0;

  curtime = (unsigned)time(NULL);
  if ((fps = curtime - lasttime) > 0)
    {
      fps = nbframe / fps;
      if (maxfps < fps)
	maxfps = fps;
      std::cout << fps << " from " << maxfps << std::endl;
      lasttime = curtime;
      nbframe = 0;
    }
  else
    nbframe++;
}

int main()
{
  Bomberman::Core	engine;

  if (!engine.initialize())
    {
      std::cout << "Initialize failed" << std::endl;
      return (EXIT_FAILURE);
    }
  engine.intro();
  engine.firstMenu();
  std::cout << "OK" << std::endl;
  while (!engine.isOver())
    {
      while (!engine.isOver() && engine.update() == true)
	{
	  // showfps();
	  engine.draw();
	}
    }
  return EXIT_SUCCESS;
}
