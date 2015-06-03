#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

BombTimer::BombTimer(Player *player, unsigned int range, IBomb *bomb)
  : Timer(bomb->getDuration() * 1000000), _player(player), _range(range), _bomb(bomb), _x(_player->getX()), _y(_player->getY())
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

Player*		BombTimer::getPlayer() const
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

unsigned int	BombTimer::getX() const
{
  return _x;
}

unsigned int	BombTimer::getY() const
{
  return _y;
}

bool		BombTimer::finish(unsigned int x, unsigned int y, Map *map)
{
  if (isFinished())
    {
      _bomb->explose(x, y, map, getRange());
      _player->incBomb();
      return true;
    }
  return false;
}

}
