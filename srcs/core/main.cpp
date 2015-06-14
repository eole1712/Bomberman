#include <iostream>
#include <stdexcept>
#include "Core.hpp"

int			main()
{
  Bomberman::Core	engine;

  try
    {
      if (!engine.initialize())
	{
	  std::cout << "Initialize failed" << std::endl;
	  return (EXIT_FAILURE);
	}
      engine.intro();
      while (!engine.isOver())
	{
	  engine.firstMenu();
	  while (!engine.isOver() && engine.update() == true)
	    engine.draw();
	}
    }
  catch (std::exception const& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
