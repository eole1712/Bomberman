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
  unsigned int		bra[2] = {20, 20};
  Bomberman::Game	engine(bra[0], bra[1]);

  if (!engine.initialize2())
    {
      std::cout << "Initialize failed" << std::endl;
      return (EXIT_FAILURE);
    }
  while (engine.update() == true)
    {
      engine.draw(engine.getContext(0), engine.getClock(0), engine.getShader(0), engine.getCamera(0));
      engine.draw(engine.getContext(1), engine.getClock(1), engine.getShader(1), engine.getCamera(1));
      engine.change();
    }
  return EXIT_SUCCESS;
}
