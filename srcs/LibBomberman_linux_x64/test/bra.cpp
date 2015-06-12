#include <cstdlib>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MyGame.hpp"

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
      printf("%d fps - %d max\n", fps, maxfps);
      lasttime = curtime;
      nbframe = 0;
    }
  else
    nbframe++;
}

int main()
{
  MyGame	engine;

  if (engine.initialize() == false)
    return (EXIT_FAILURE);
  while (engine.update() == true)
    {
      showfps();
      engine.draw();
      engine.draw();
    }
  return EXIT_SUCCESS;
}
