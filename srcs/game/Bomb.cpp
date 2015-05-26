#include "Bomb.hpp"

namespace Bomberman
{

Bomb::Bomb(IObject *player, unsigned int range)
  : Timer(5), _player(player), _range(range)
{
  start();
}

Bomb::~Bomb()
{

}

unsigned int	Bomb::getRange() const
{
  return _range;
}

IObject*	Bomb::getPlayer() const
{
  return _player;
}

}
