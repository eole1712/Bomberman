#include "BombFactory.hpp"
#include "BombClassic.hpp"

namespace Bomberman
{
  namespace Bomb
  {
    Factory::Factory()
    {
      learn(new Bomberman::Bomb::Classic);
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
