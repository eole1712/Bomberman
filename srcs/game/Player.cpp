#include <string>
#include <list>
#include <cmath>
#include <iostream>
#include "Player.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "my_random.hpp"

namespace Bomberman
{

unsigned int const	Player::dftRange = 3;
unsigned int const	Player::dftSpeed = 1;
unsigned int const	Player::dftShield = 0;
unsigned int const	Player::dftBomb = 1;
IBomb::Type const	Player::dftBombType = IBomb::CLASSIC;

Player::Player(std::string const &name, glm::vec4 color)
  : IObject(), _name(name), _isAlive(true), _isParalyzed(false), _zeroBomb(false), _range(dftRange), _speed(dftSpeed), _shield(dftShield), _bomb(dftBomb), _bombType(dftBombType), _color(color), animation()
{
  _buffOn[IBuff::INC_SPEED] = &Player::incSpeed;
  _buffOn[IBuff::DEC_SPEED] = &Player::decSpeed;
  _buffOn[IBuff::INC_BOMB] = &Player::incBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::incRange;
  _buffOn[IBuff::NO_BOMB] = &Player::disableAttack;
  _buffOn[IBuff::PARALYZED] = &Player::paralyze;
  _buffOn[IBuff::SHIELD] = &Player::incShield;
  _buffOn[IBuff::WEAPON] = &Player::randWeapon;

  _buffOff[IBuff::INC_SPEED] = &Player::decSpeed;
  _buffOff[IBuff::DEC_SPEED] = &Player::incSpeed;
  _buffOff[IBuff::INC_BOMB] = &Player::decBomb;
  _buffOff[IBuff::INC_RANGE] = &Player::decRange;
  _buffOff[IBuff::NO_BOMB] = &Player::enableAttack;
  _buffOff[IBuff::PARALYZED] = &Player::unparalyze;
  _buffOff[IBuff::SHIELD] = &Player::decShield;
  _buffOff[IBuff::WEAPON] = &Player::randWeapon;
}

Player::Player()
  : _name("NoName"), _isAlive(true), _isParalyzed(false), _zeroBomb(false), _range(dftRange), _speed(dftSpeed), _shield(dftShield), _bomb(dftBomb), _bombType(dftBombType), _color(glm::vec4(1))
{
  _buffOn[IBuff::INC_SPEED] = &Player::incSpeed;
  _buffOn[IBuff::DEC_SPEED] = &Player::decSpeed;
  _buffOn[IBuff::INC_BOMB] = &Player::incBomb;
  _buffOn[IBuff::INC_RANGE] = &Player::incRange;
  _buffOn[IBuff::NO_BOMB] = &Player::disableAttack;
  _buffOn[IBuff::PARALYZED] = &Player::paralyze;
  _buffOn[IBuff::SHIELD] = &Player::incShield;
  _buffOn[IBuff::WEAPON] = &Player::randWeapon;

  _buffOff[IBuff::INC_SPEED] = &Player::decSpeed;
  _buffOff[IBuff::DEC_SPEED] = &Player::incSpeed;
  _buffOff[IBuff::INC_BOMB] = &Player::decBomb;
  _buffOff[IBuff::INC_RANGE] = &Player::decRange;
  _buffOff[IBuff::NO_BOMB] = &Player::enableAttack;
  _buffOff[IBuff::PARALYZED] = &Player::unparalyze;
  _buffOff[IBuff::SHIELD] = &Player::decShield;
  _buffOff[IBuff::WEAPON] = &Player::randWeapon;
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
  return _zeroBomb || (_bomb == 0);
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
  if (_range > 2)
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
  if (_speed > 1)
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
  if (_shield > 0)
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

void			Player::randWeapon()
{
  std::cout << "Rand Bomb"  << std::endl;
  setBombType((IBomb::Type)(my_random(1, IBomb::nbBomb - 1)));
}

// buff methods
void			Player::addBuff(IBuff *n)
{
  (this->*_buffOn[n->getBuffType()])();
  if (n->getDuration() != IBuff::infinite)
    {
      BuffTimer		*buff = new BuffTimer(n);

      _buff.push_back(buff);
      buff->start();
    }
}

void			Player::addTimedBuff(Bomberman::BuffTimer *buff)
{
  (this->*_buffOn[buff->getBuff()->getBuffType()])();
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
	  it = _buff.erase(it);
	}
    }
}

std::list<BuffTimer*> const& Player::getBuffList() const
{
  return _buff;
}

// position methods

void			Player::initGame(unsigned int x, unsigned int y, Map *map)
{
  if (map)
    {
      _map = map;
      if (_map->getWidth() > x && _map->getHeight() > y)
	{
	  setPosition(glm::vec3(x, 0, y));
	}
    }
}

void			Player::initGame(Map *map)
{
  if (map)
    {
      _map = map;
      for (unsigned int y = 0; y < _map->getHeight(); ++y)
	{
	  for (unsigned int x = 0; x < _map->getWidth(); ++x)
	    {
	      if (_map->getCellValue(x, y)->getObjectType() == IObject::SPAWN)
		{
		  setPosition(glm::vec3(x + 0.5, 0, y + 0.5));
		  _map->setCellValue(x, y, _map->getRcs()->getObject(IObject::EMPTY));
		  return;
		}
	    }
	}
    }
  std::cout << "Pas de spawn" << std::endl;
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

void			Player::move(float const & direction, float const & elsapsedTime)
{
  glm::vec3		pos;
  glm::vec3		npos;
  IObject::Type		type;
  float			speedbra;

  if (!isAlive() || isParalyzed())
    return ;
  speedbra = _speed * elsapsedTime;
  pos = glm::rotate(glm::vec3(0, 0, 0.06), direction, glm::vec3(0, 1, 0)) * speedbra;
  npos = getPosition() + pos;
  if (npos.x > 0 && npos.x < _map->getWidth())
    {
      type = _map->getCellValue(int(npos.x), int(getPosition().z))->getObjectType();
      if ((type != IObject::DESTROYABLEWALL && type != IObject::WALL && type != IObject::BOMB) ||
	  (int(npos.x) == int(getX()) && int(getPosition().z) == int(getY())))
	translate(glm::vec3(pos.x, 0, 0));
    }
  if (npos.z > 0 && npos.z < _map->getHeight())
    {
      type = _map->getCellValue(int(getPosition().x), int(npos.z))->getObjectType();
      if ((type != IObject::DESTROYABLEWALL && type != IObject::WALL && type != IObject::BOMB) ||
	  (int(getPosition().x) == int(getX()) && int(npos.z) == int(getY())))
	translate(glm::vec3(0, 0, pos.z));
    }
  if (_map->getCellValue(getX(), getY())->getObjectType() == IObject::BONUS)
    {
      addBuff(dynamic_cast<IBuff*>(_map->getCellValue(getX(), getY())));
      _map->killObject(getX(), getY());
    }
  if (_map->getCellValue(getX(), getY())->getObjectType() == IObject::FIRE)
    {
      tryToKill();
    }
  if (_map->getCellValue(getX(), getY())->getObjectType() == IObject::BOMB2)
    {
      dynamic_cast<BombTimer*>(_map->getCellValue(getX(), getY()))->setFinished();
    }
}

void			Player::rotate(bool const & direction,
				       float const & elsapsedTime, float const & stop)
{
  float			before;
  float			after;

  before = getRotation().y;
  rotate(direction, elsapsedTime);
  after = getRotation().y;
  after -= 360 * (stop == 0 && direction == 1);
  before -= 360 * (stop == 0 && direction == 1);
  if (abs(stop - before) < abs(stop - after))
    setRotation(glm::vec3(0, stop, 0));
}

void			Player::rotate(bool const & direction,
				       float const & elsapsedTime)
{
  glm::vec3		rot;

  if (!isAlive() || isParalyzed())
    return;
  rot = getRotation();
  if (direction)
    setRotation(glm::vec3(rot.x, fmod(getRotation().y + 3 * elsapsedTime * _speed, 360), rot.z));
  else
    {
      if (rot.y - 3 * elsapsedTime * _speed < 0)
	setRotation(glm::vec3(rot.x, 360 + rot.y - 3 * elsapsedTime * _speed, rot.z));
      else
	setRotation(glm::vec3(rot.x, rot.y - 3 * elsapsedTime * _speed, rot.z));
    }
}

void			Player::moveUp(float const & elsapsedTime)
{
  move(0, elsapsedTime);
  if (getRotation().y != 0)
    rotate((getRotation().y > 180), elsapsedTime, 0);
}

void			Player::moveRight(float const & elsapsedTime)
{
  move(90, elsapsedTime);
  if (getRotation().y != 90)
    rotate((getRotation().y < 90 || getRotation().y > 270), elsapsedTime, 90);
}

void			Player::moveDown(float const & elsapsedTime)
{

  move(180, elsapsedTime);
  if (getRotation().y != 180)
    rotate((getRotation().y < 180), elsapsedTime, 180);
}

void			Player::moveLeft(float const & elsapsedTime)
{
  move(270, elsapsedTime);
  if (getRotation().y != 270)
    rotate((getRotation().y < 270 && getRotation().y >= 90), elsapsedTime, 270);
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

      _map->addBomb(bombT);
      _map->setCellValue(getX(), getY(), bombT);
      decBomb();
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
      return false;
    }
  return true;
}

// color
void			Player::setColor(glm::vec4 color)
{
  _color = color;
}

glm::vec4		Player::getColor() const
{
  return _color;
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
