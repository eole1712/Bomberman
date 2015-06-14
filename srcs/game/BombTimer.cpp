#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

BombTimer::BombTimer(Player *player, unsigned int range, IBomb *bomb)
  : Timer(bomb->getDuration() * 1000000), _player(player), _range(range), _bomb(bomb), _x(_player->getX()), _y(_player->getY()), _isFinished(false), _isVirus(false), _byPlayer(false)
{
  if (bomb->getBombType() == Bomb::MINE)
    {
      player->incBomb();
    }
  player->setBombType(Bomb::CLASSIC);
  start();
}

BombTimer::BombTimer(Player *player, unsigned int range, IBomb *bomb, float time, unsigned int x, unsigned int y, bool isVirus)
  : Timer(time * 1000000), _player(player), _range(range), _bomb(bomb), _x(x), _y(y), _isFinished(false), _isVirus(isVirus), _byPlayer(false)
{
  if (_bomb == NULL)
    std::cout << "c'est null" << std::endl;
  if (!_isVirus && bomb->getBombType() == Bomb::MINE)
    {
      player->incBomb();
    }
  player->setBombType(Bomb::CLASSIC);
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

void		BombTimer::setFinished(bool byPlayer)
{
  _isFinished = true;
  _byPlayer = byPlayer;
}

bool		BombTimer::finish(unsigned int x, unsigned int y, Map *map)
{
  if (isFinished() || _isFinished)
    {
      if (_isFinished == true &&
	  (_byPlayer && _bomb->getBombType() == Bomb::MINE && getElapsedTime() < 3000000))
	{
	  _isFinished = false;
	  return false;
	}
      _bomb->explose(x, y, map, getRange(), _player);
      map->getRcs()->getSound(Bomberman::RessourceStock::EXPLOSE)->play();
      if (!_isVirus)
	_player->incBomb();
      return true;
    }
  return false;
}

void		BombTimer::setBlastRangeToMap(AI::StateMap* map, Map const* realMap) const
{
  _bomb->setBlastRangeToMap(map, realMap, _x, _y, _range);
}
}
