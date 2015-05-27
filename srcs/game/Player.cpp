#include <string>
#include <list>
#include <cmath>
#include "Player.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

unsigned int const	Player::dftRange = 0;
unsigned int const	Player::dftSpeed = 0;
unsigned int const	Player::dftShield = 0;
unsigned int const	Player::dftBomb = 0;

Player::Player(std::string const &name, unsigned int x, unsigned int y)
  : IObject(), _name(name), _isAlive(true), _isParalyzed(false), _zeroBomb(false), _range(dftRange), _speed(dftSpeed), _shield(dftShield), _bomb(dftBomb), _x(x), _y(y)
{
  _buffOn[IBuff::INC_SPEED] = &Player::incSpeed;
  _buffOn[IBuff::DEC_SPEED] = &Player::decSpeed;
  _buffOn[IBuff::INC_BOMB] = &Player::incBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::incRange;
  _buffOn[IBuff::NO_BOMB] = &Player::disableAttack;
  _buffOn[IBuff::PARALYZED] = &Player::paralyze;
  _buffOn[IBuff::SHIELD] = &Player::incShield;

  _buffOff[IBuff::INC_SPEED] = &Player::decSpeed;
  _buffOff[IBuff::DEC_SPEED] = &Player::incSpeed;
  _buffOff[IBuff::INC_BOMB] = &Player::decBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::decRange;
  _buffOff[IBuff::NO_BOMB] = &Player::enableAttack;
  _buffOff[IBuff::PARALYZED] = &Player::unparalyze;
  _buffOff[IBuff::SHIELD] = &Player::decShield;
}

Player::Player()
  : _name("NoName"), _isAlive(true), _isParalyzed(false), _zeroBomb(false), _range(dftRange), _speed(dftSpeed), _shield(dftShield), _bomb(dftBomb), _x(0), _y(0)
{
  _buffOn[IBuff::INC_SPEED] = &Player::incSpeed;
  _buffOn[IBuff::DEC_SPEED] = &Player::decSpeed;
  _buffOn[IBuff::INC_BOMB] = &Player::incBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::incRange;
  _buffOn[IBuff::NO_BOMB] = &Player::disableAttack;
  _buffOn[IBuff::PARALYZED] = &Player::paralyze;
  _buffOn[IBuff::SHIELD] = &Player::incShield;

  _buffOff[IBuff::INC_SPEED] = &Player::decSpeed;
  _buffOff[IBuff::DEC_SPEED] = &Player::incSpeed;
  _buffOff[IBuff::INC_BOMB] = &Player::decBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::decRange;
  _buffOff[IBuff::NO_BOMB] = &Player::enableAttack;
  _buffOff[IBuff::PARALYZED] = &Player::unparalyze;
  _buffOff[IBuff::SHIELD] = &Player::decShield;
}

Player::~Player()
{
  for (std::list<BuffTimer*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    {
      delete *it;
    }
}

// getters

std::string const&	Player::getName() const
{
  return _name;
}

unsigned int   		Player::getRange() const
{
  return _range;
}

unsigned int   		Player::getSpeed() const
{
  return _speed;
}


// check status

bool			Player::isAlive() const
{
  return _isAlive;
}

bool			Player::isParalyzed() const
{
  return _isParalyzed;
}

bool			Player::zeroBomb() const
{
  return _zeroBomb;
}

bool			Player::canAbsorb() const
{
  return (_shield > 0);
}

// range methods

void			Player::incRange()
{
  _range++;
}

void			Player::decRange()
{
  _range--;
}

void			Player::resetRange()
{
  _range = dftRange;
}

// speed methods

void			Player::incSpeed()
{
  _speed++;
}

void			Player::decSpeed()
{
  _speed--;
}

void			Player::resetSpeed()
{
  _speed = dftSpeed;
}

// shield methods

void			Player::incShield()
{
  _shield++;
}

void			Player::decShield()
{
  _shield--;
}

void			Player::resetShield()
{
  _shield = dftShield;
}

// bomb methods

void			Player::incBomb()
{
  _bomb++;
}

void			Player::decBomb()
{
  _bomb--;
}

void			Player::resetBomb()
{
  _bomb = dftBomb;
}

void			Player::enableAttack()
{
  _zeroBomb = false;
}

void			Player::disableAttack()
{
  _zeroBomb = true;
}

// paralyze methods

void			Player::paralyze()
{
  _isParalyzed = true;
}

void			Player::unparalyze()
{
  _isParalyzed = false;
}

// buff methods
void			Player::addBuff(IBuff *n)
{
  BuffTimer		*buff = new BuffTimer(n);


  (this->*_buffOn[n->getBuffType()])();
  _buff.push_back(buff);
  buff->start();
}

void			 Player::checkBuffList()
{
  for (std::list<BuffTimer*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    {
      if ((*it)->isFinished())
	{
	  (this->*_buffOff[(*it)->getBuff()->getBuffType()])();
	  delete (*it);
	  _buff.erase(it);
	}
    }
}

// position methods

void			Player::initGame(unsigned int x, unsigned int y, Map *map)
{
  if (map)
    {
      map = _map;
      if (_map->getWidth() > x && _map->getHeight() > y)
	{
	  setPosition(glm::vec3(x, 0, y));
	}
    }
}

unsigned int		Player::getX() const
{
  return floor(getPosition().x);
}

float			Player::getfX() const
{
  return getPosition().x;
}

unsigned int		Player::getY() const
{
  return floor(getPosition().z);
}

float			Player::getfY() const
{
  return getPosition().z;
}

void			Player::setX(float x)
{
  setPosition(glm::vec3(x, 0, getPosition().z));
}

void			Player::setY(float y)
{
  setPosition(glm::vec3(getPosition().x, 0, y));
}

void			Player::move(glm::vec3 pos)
{
  glm::vec3		npos;
  IObject::Type		type;

  if (!isAlive() && isParalyzed())
    return;
  npos = getPosition() + pos;
  type = _map->getCellValue(floor(npos.x), floor(npos.z))->getObjectType();
  if (npos.x < 1 || npos.x > _map->getWidth() ||
      type == IObject::DESTROYABLEWALL || type == IObject::WALL)
    npos = glm::vec3(getPosition().x, npos.y, npos.z);
  type = _map->getCellValue(floor(npos.x), floor(npos.z))->getObjectType();
  if (npos.y < 1 || npos.y > _map->getHeight() ||
      type == IObject::DESTROYABLEWALL || type == IObject::WALL)
    npos = glm::vec3(npos.x, npos.y, getPosition().z);
  setPosition(npos);
}

//attacks

void			Player::setBombType(IBomb::Type type)
{
  _bombType = type;
}

IBomb::Type		Player::getBombType() const
{
  return _bombType;
}

void			Player::putBomb()
{
  if (_map && isAlive() && !isParalyzed() && !zeroBomb())
    {
      IBomb	*bomb = dynamic_cast<IBomb*>(_map->getRcs()->getBomb(getBombType()));
      BombTimer	*bombT = new BombTimer(this, getRange(), bomb);
      _map->setCellValue(getX(), getY(), bombT);
    }
}

bool			Player::tryToKill()
{
  if (isAlive())
    {
      if (canAbsorb())
	decShield();
      else
	{
	  _isAlive = false;
	  return true;
	}
    }
  return false;
}


// type

IObject::Type		Player::getObjectType() const
{
  return IObject::PLAYER;
}

bool			Player::isNull() const
{
  return false;
}
}
