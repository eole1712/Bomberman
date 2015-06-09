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
  unsigned int		bra[2] = {10, 10};
  Bomberman::Game	engine(bra[0], bra[1]);

  if (!engine.initialize())
    {
      std::cout << "Initialize failed" << std::endl;
      return (EXIT_FAILURE);
    }
  while (engine.update() == true)
    {
      glViewport(900, 0, 900, 900);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      engine.draw(engine.getClock(), engine.getShader(), engine.getCamera(0));
      glViewport(0, 0, 900, 900);
      engine.draw(engine.getClock(), engine.getShader(), engine.getCamera(1));
      engine.getContext().flush();
    }
  return EXIT_SUCCESS;
}
