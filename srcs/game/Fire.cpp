#include "Map.hpp"
#include "Fire.hpp"

namespace Bomberman
{

const float	Fire::explosionTime = 0.3;

Fire::Fire(Player *player, unsigned int x, unsigned int y)
  : Timer(explosionTime * 1000000), _player(player), _x(x), _y(y)
{
  start();
}

Fire::~Fire()
{
  std::cout << "feu est mor" << std::endl;
}

Player*		Fire::getPlayer() const
{
  return _player;
}

IObject::Type	Fire::getObjectType() const
{
  return IObject::FIRE;
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
