#include "BuffFactory.hpp"
#include "BuffNoBomb.hpp"
#include "BuffShield.hpp"
#include "BuffIncBomb.hpp"
#include "BuffDecSpeed.hpp"
#include "BuffIncRange.hpp"
#include "BuffParalyzed.hpp"
#include "BuffIncSpeed.hpp"

namespace Bomberman
{
  namespace Buff
  {
    Factory::Factory()
    {
      learn(new Bomberman::Buff::Shield);
      learn(new Bomberman::Buff::NoBomb);
      learn(new Bomberman::Buff::IncBomb);
      learn(new Bomberman::Buff::IncSpeed);
      learn(new Bomberman::Buff::IncRange);
      learn(new Bomberman::Buff::DecSpeed);
      learn(new Bomberman::Buff::Paralyzed);
    }

    Factory::~Factory()
    {
      ;
    }

  SmartFactory<IBuff>* Factory::getInstance()
  {
    if (_instance == NULL)
      _instance = new Factory();
    return (_instance);
  }

  }
}
