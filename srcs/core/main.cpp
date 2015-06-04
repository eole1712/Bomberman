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
#include "Game.hpp"

int main()
{
  unsigned int		bra[2] = {15, 15};
  Bomberman::Game	engine(bra[0], bra[1]);

  if (engine.initialize() == false)
    return (EXIT_FAILURE);
  while (engine.update() == true)
    engine.draw();
  return EXIT_SUCCESS;
}
