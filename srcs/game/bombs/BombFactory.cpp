#include "BombFactory.hpp"
#include "BombClassic.hpp"
#include "BombMine.hpp"
#include "BombBarrel.hpp"
#include "BombVirus.hpp"

namespace Bomberman
{
  namespace Bomb
  {
    Factory::Factory()
    {
      learn(new Bomberman::Bomb::Classic);
      learn(new Bomberman::Bomb::Mine);
      learn(new Bomberman::Bomb::Barrel);
      learn(new Bomberman::Bomb::Virus);
    }
    Factory::~Factory()
    {
      ;
    }

  SmartFactory<IBomb>* Factory::getInstance()
  {
    if (_instance == NULL)
      _instance = new Factory();
    return (_instance);
  }

  }
}
