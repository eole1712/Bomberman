#include <cstdlib>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MyGame.hpp"

int main(int argc, char **argv)
{
  MyGame	engine;

  if (engine.initialize() == false)
    return (EXIT_FAILURE);
  while (engine.update() == true)
    engine.draw();
  return EXIT_SUCCESS;
}
