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

int	main()
{
  Bomberman::IBuff* lol;
  Bomberman::IBuff* lal;
  Bomberman::IBuff const* lul;
  std::vector<std::string>	vec;

  vec.push_back("Adrien");
  vec.push_back("Léon");

  Bomberman::RessourceStock	stock(vec);
  Bomberman::Map	yooooo("blibi", 10, 10, 2, Bomberman::Map::EASY, &stock);

  Bomberman::Buff::Factory::getInstance()->learn(new Bomberman::Buff::IncSpeed());
  Bomberman::Buff::Factory::getInstance()->learn(new Bomberman::Buff::Paralyzed());

  Bomberman::IObject *p;
  p = new Bomberman::Player("Hello", 0, 0);

  lol = Bomberman::Buff::Factory::getInstance()->generate("IncSpeed");
  lal = Bomberman::Buff::Factory::getInstance()->generate("Paralyzed");
  lul = Bomberman::Buff::Factory::getInstance()->getObject("Paralyzed");
  std::cout << lol->getClassName() << std::endl;
  std::cout << lal->getClassName() << std::endl;
  std::cout << lul->getClassName() << std::endl;
  delete lol;
  delete lal;
  delete p;
  return (EXIT_SUCCESS);
}
