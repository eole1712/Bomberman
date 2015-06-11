#include "Core.hpp"

int main()
{
  Bomberman::Core	engine;

  if (!engine.initialize())
    {
      std::cout << "Initialize failed" << std::endl;
      return (EXIT_FAILURE);
    }
  engine.firstMenu();
  while (engine.update() == true)
    {
      engine.draw();
    }
  return EXIT_SUCCESS;
}
