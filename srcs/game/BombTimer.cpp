#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

BombTimer::BombTimer(IObject *player, unsigned int range, IBomb *bomb)
  : Timer(bomb->getDuration()), _player(player), _range(range), _bomb(bomb)
{
  start();
}

BombTimer::~BombTimer()
{

}

unsigned int	BombTimer::getRange() const
{
  return _range;
}

IObject*	BombTimer::getPlayer() const
{
  return _player;
}

IBomb*		BombTimer::getBombType() const
{
  return _bomb;
}

IObject::Type	BombTimer::getObjectType() const
{
  return IObject::BOMB;
}

bool		BombTimer::isNull() const
{
  return false;
}

void		BombTimer::finish(unsigned int x, unsigned int y, Map *map)
{
  if (isFinished())
    {
      _bomb->explose(x, y, map);
    }
}

}
