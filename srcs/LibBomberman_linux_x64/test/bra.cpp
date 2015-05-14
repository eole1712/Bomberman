#include <cstdlib>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MyGame.hpp"

int main(int argc, char **argv)
{
  MyGame	engine;
  Object	*tmp;

  if (engine.initialize() == false)
    return (EXIT_FAILURE);
  for (int i = 1; i < argc; i++)
    {
      tmp = new Object(argv[i++]);
      tmp->scale(glm::vec3(atoi(argv[i])));
      engine.attachObject(tmp);
    }
  while (engine.update() == true)
    engine.draw();
  return EXIT_SUCCESS;
}
