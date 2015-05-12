#include <cstdlib>
#include <iostream>
#include "BuffFactory.hpp"
#include "BuffIncSpeed.hpp"

int	main()
{
  Bomberman::IBuff* lol;
  Bomberman::IBuff* lal;

  Bomberman::Buff::Factory::getInstance()->learn(new Bomberman::Buff::IncSpeed());
  Bomberman::Buff::Factory::getInstance()->learn(new Bomberman::Buff::IncSpeed());

  lol = Bomberman::Buff::Factory::getInstance()->generate("lol");
  lal = Bomberman::Buff::Factory::getInstance()->generate("lal");
  std::cout << lol->getDuration() << std::endl;
  std::cout << lal->getType() << std::endl;
  return (EXIT_SUCCESS);
}
