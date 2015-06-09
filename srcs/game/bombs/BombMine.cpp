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

Bomb::Type	Mine::getBombType() const
{
  return Bomb::MINE;
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

void		Mine::setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					 int y, unsigned int range) const
{
  static_cast<void>(map);
  static_cast<void>(realMap);
  static_cast<void>(x);
  static_cast<void>(y);
  static_cast<void>(range);
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
