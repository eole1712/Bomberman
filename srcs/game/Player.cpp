#include <string>
#include <list>
#include "Player.hpp"

Bomberman::Player::Player(std::string const &name)
  : _name(name), _range(defRange), _speed(defSpeed), _isAlive(true)
{

}

Bomberman::Player::~Player()
{
  for (std::list<IBuff*>::iterator it = _buff.begin(); it != _buff.end(); it++)
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

template<>
void			Bomberman::Player::execBuff<Bomberman::IBuff::INC_SPEED>(Bomberman::IBuff *n)
{
  incSpeed();
}

template<>
void			Bomberman::Player::execBuff<Bomberman::IBuff::DEC_SPEED>(Bomberman::IBuff *n)
{
  decSpeed();
}

template<>
void			Bomberman::Player::execBuff<Bomberman::IBuff::INC_BOMB>(Bomberman::IBuff *n)
{
  ;
}

template<>
void			Bomberman::Player::execBuff<Bomberman::IBuff::NO_BOMB>(Bomberman::IBuff *n)
{
  _maxBomb = 0;
}

template<>
void			Bomberman::Player::execBuff<Bomberman::IBuff::PARALYZED>(Bomberman::IBuff *n)
{
  _maxBomb = 0;
}


template<>
void			Bomberman::Player::execBuff<Bomberman::IBuff::SHIELD>(Bomberman::IBuff *n)
{
  ;
}

void			Bomberman::Player::addBuff(Bomberman::IBuff *n)
{
  _buff.push_back(n);
}

void			Bomberman::Player::delBuff(Bomberman::IBuff *n)
{
  for (std::list<IBuff*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    {
      if (*it == n)
	{
	  _buff.remove_if(it);
	  return;
	}
    }
}

void			 Bomberman::Player::checkBuffList()
{
  for (std::list<IBuff*>::iterator it = _buff.begin(); it != _buff.end(); it++)
    {
      ;
    }
}
