#include "Map.hpp"
#include "Fire.hpp"

namespace Bomberman
{

const float	Fire::explosionTime = 0.5;

Fire::Fire(Player *player, unsigned int x, unsigned int y)
  : Timer(explosionTime * 1000000), _player(player), _x(x), _y(y), _buff(NULL)
{
  start();
}

Fire::Fire(Player *player, unsigned int x, unsigned int y, float time)
  : Timer(time * 1000000), _player(player), _x(x), _y(y), _buff(NULL)
{
  start();
}

Fire::~Fire()
{

}

Player*		Fire::getPlayer() const
{
  return _player;
}

IObject::Type	Fire::getObjectType() const
{
  return IObject::FIRE;
}

IObject*	Fire::getBuff() const
{
  return _buff;
}

void		Fire::setBuff(IObject* buff)
{
  _buff = buff;
}

bool		Fire::isNull() const
{
  return false;
}

unsigned int	Fire::getX() const
{
  return _x;
}

unsigned int	Fire::getY() const
{
  return _y;
}

}
