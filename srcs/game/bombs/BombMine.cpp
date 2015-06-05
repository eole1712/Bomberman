#include "IBuff.hpp"
#include "BombMine.hpp"
#include "my_random.hpp"

namespace Bomberman
{

namespace Bomb
{

Mine::Mine()
{}

Mine::~Mine()
{}

int		Mine::getDuration() const
{
  return 60;
}

IBomb::Type	Mine::getBombType() const
{
  return IBomb::MINE;
}

IObject::Type	Mine::getObjectType() const
{
  return IObject::BOMB2;
}

bool		Mine::isNull() const
{
  return false;
}

void		Mine::explose(int x, int y, Map *map, unsigned int, Player *player) const
{
  isOtherBomb(map, x, y, player, x, y);
}

IBomb*		Mine::clone() const
{
  return new Mine;
}

std::string	Mine::getClassName() const
{
  return "Mine";
}

}

}
