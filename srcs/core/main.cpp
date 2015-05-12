#include <cstdlib>
#include <iostream>
#include "BuffFactory.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffParalyzed.hpp"

int	main()
{
  Bomberman::IBuff* lol;
  Bomberman::IBuff* lal;

  Bomberman::Buff::Factory::getInstance()->learn(new Bomberman::Buff::IncSpeed());
  Bomberman::Buff::Factory::getInstance()->learn(new Bomberman::Buff::Paralyzed());

  lol = Bomberman::Buff::Factory::getInstance()->generate("IncSpeed");
  lal = Bomberman::Buff::Factory::getInstance()->generate("Paralyzed");
  std::cout << lol->getClassName() << std::endl;
  std::cout << lal->getClassName() << std::endl;
  return (EXIT_SUCCESS);
}
