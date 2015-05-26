#include <string>
#include "RessourceStock.hpp"
#include "BuffDecSpeed.hpp"
#include "BuffFactory.hpp"
#include "BuffIncBomb.hpp"
#include "BuffIncRange.hpp"
#include "BuffIncSpeed.hpp"
#include "BuffNoBomb.hpp"
#include "BuffParalyzed.hpp"
#include "BuffShield.hpp"
#include "Empty.hpp"
#include "IBomb.hpp"
#include "BombClassic.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

RessourceStock::RessourceStock(std::vector<std::string> const &names)
  : _players(names.size(), NULL), _buffs(IBuff::nbBuff, NULL), _bombs(IBomb::nbBomb, NULL), _objects(IObject::nbObject, NULL)
{
  for (unsigned int i = 0; i < names.size(); ++i)
    _players[i] = new Player(names[i], 0, 0);
  _buffs[IBuff::INC_SPEED] = new Buff::IncSpeed;
  _buffs[IBuff::DEC_SPEED] = new Buff::DecSpeed;
  _buffs[IBuff::INC_BOMB] = new Buff::IncBomb;
  _buffs[IBuff::INC_RANGE] = new Buff::IncRange;
  _buffs[IBuff::NO_BOMB] = new Buff::NoBomb;
  _buffs[IBuff::PARALYZED] = new Buff::Paralyzed;
  _buffs[IBuff::SHIELD] = new Buff::Shield;
  _bombs[IBomb::CLASSIC] = new Bomb::Classic;
  _objects[IObject::BOMB] = NULL;
  _objects[IObject::PLAYER] = NULL;
  _objects[IObject::BONUS] = NULL;
  _objects[IObject::WALL] = NULL;
  _objects[IObject::DESTROYABLEWALL] = NULL;
  _objects[IObject::EMPTY] = new Empty;
}

RessourceStock::~RessourceStock()
{
  for (unsigned int i = 0; i < _players.size(); ++i)
    {
      delete _players[i];
    }
  for (unsigned int i = 0; i < _buffs.size(); ++i)
    {
      delete _buffs[i];
    }
  for (unsigned int i = 0; i < _objects.size(); ++i)
    {
      delete _objects[i];
    }
}

IObject		*RessourceStock::getObject(IObject::Type type) const
{
  return _objects[type];
}

IObject		*RessourceStock::getBuff(IBuff::Type type) const
{
  return _buffs[type];
}

IObject		*RessourceStock::getPlayer(std::string const &name) const
{
  for (unsigned int i = 0; i < _players.size(); ++i)
    {
      if ((dynamic_cast<Player *>(_players[i])->getName()) == name)
	  return _players[i];
    }
  return NULL; //EXCEPTION???
}

IObject		*RessourceStock::getPlayer(unsigned int id) const
{
  if (id >= _players.size())
    return NULL; //EXCEPTION???
  return _players[id];
}

}
