#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

BombTimer::BombTimer(Player *player, unsigned int range, IBomb *bomb)
  : Timer(bomb->getDuration() * 1000000), _player(player), _range(range), _bomb(bomb), _x(_player->getX()), _y(_player->getY()), _isFinished(false)
{
  std::cout << bomb->getClassName() << std::endl;
  if (bomb->getBombType() == IBomb::MINE)
    {
      player->incBomb();
    }
  player->setBombType(IBomb::CLASSIC);
  start();
}

BombTimer::BombTimer(Player *player, unsigned int range, IBomb *bomb, float time, unsigned int x, unsigned int y)
  : Timer(time * 1000000), _player(player), _range(range), _bomb(bomb), _x(x), _y(y), _isFinished(false)
{
  if (bomb->getBombType() == IBomb::MINE)
    {
      player->incBomb();
    }
  player->setBombType(IBomb::CLASSIC);
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
  return _bomb->getObjectType();
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

void		BombTimer::setFinished()
{
  _isFinished = true;
}

bool		BombTimer::finish(unsigned int x, unsigned int y, Map *map)
{
  if (isFinished() || _isFinished)
    {
      if (_isFinished == true && _bomb->getBombType() == IBomb::MINE && getElapsedTime() < 1000000)
	{
	  _isFinished = false;
	  return false;
	}
      _bomb->explose(x, y, map, getRange(), _player);
      _player->incBomb();
      return true;
    }
  return false;
}

}
