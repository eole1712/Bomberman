#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "RessourceStock.hpp"
#include "Map.hpp"
#include "BuffFactory.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffParalyzed.hpp"
#include "Player.hpp"
#include "Gamer.hpp"
#include "Core.hpp"

int main()
{
  Bomberman::Core	engine;

  if (!engine.initialize())
    {
      std::cout << "Initialize failed" << std::endl;
      return (EXIT_FAILURE);
    }
  engine.startGame();
  while (engine.update() == true)
    {
      engine.draw();
    }
  return EXIT_SUCCESS;
}
