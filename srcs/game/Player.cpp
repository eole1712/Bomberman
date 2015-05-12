#include <string>
#include <list>
#include "Player.hpp"

Bomberman::Player::Player(std::string const &name)
  : _name(name), _range(defRange), _speed(defSpeed), _isAlive(true)
{
  _buffOn[0] = &Player::incSpeed;
  _buffOn[1] = &Player::decSpeed;
  _buffOn[2] = &Player::incBomb;
  _buffOn[3] = &Player::disableAttack;
  _buffOn[4] = &Player::disableMove;
  _buffOn[5] = &Player::incShield;

  _buffOff[0] = &Player::decSpeed;
  _buffOff[1] = &Player::incSpeed;
  _buffOff[2] = &Player::decBomb;
  _buffOff[3] = &Player::enableAttack;
  _buffOff[4] = &Player::enableMove;
  _buffOff[5] = &Player::decShield;
}

Bomberman::Player::~Player()
{
  for (std::list<BuffTimer*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    {
      delete *it;
    }
}

// getters

std::string const&	Bomberman::Player::getName() const
{
  return _name;
}

unsigned int   		Bomberman::Player::getRange() const
{
  return _range;
}

unsigned int   		Bomberman::Player::getSpeed() const
{
  return _speed;
}

// range methods

void			Bomberman::Player::incRange()
{
  _range++;
}

void			Bomberman::Player::decRange()
{
  _range--;
}

void			Bomberman::Player::resetRange()
{
  _range = defRange;
}

// speed methods

void			Bomberman::Player::incSpeed()
{
  _speed++;
}

void			Bomberman::Player::decSpeed()
{
  _speed--;
}

void			Bomberman::Player::resetSpeed()
{
  _speed = defSpeed;
}

// isAlive

bool			Bomberman::Player::isAlive() const
{
  return _isAlive;
}

// buff methods --- pas complète
void			Bomberman::Player::addBuff(Bomberman::IBuff *n)
{
  BuffTimer		*buff = new BuffTimer(n);
  IBuff::Type		t = n->getBuffType();


  _buff.push_back(buff);
}



void			Bomberman::Player::delBuff(Bomberman::IBuff *n)
{
  // for (std::list<IBuff*>::iterator it = _buff.begin(); it != _buff.end(); it++)
  //   {
  //     if (*it == n)
  // 	{
  // 	  // _buff.remove_it(it);
  // 	  return;
  // 	}
  //   }
}

void			 Bomberman::Player::checkBuffList()
{
  // for (std::list<IBuff*>::iterator it = _buff.begin(); it != _buff.end(); it++)
  //   {
  //     ;
  //   }
}
