//
// Player.cpp for  in /home/ghukas_g/rendu/cpp_bomberman/srcs/game
//
// Made by Grisha GHUKASYAN
// Login   <ghukas_g@epitech.net>
//
// Started on  Thu May  7 16:31:13 2015 Grisha GHUKASYAN
// Last update Thu May  7 16:46:25 2015 Grisha GHUKASYAN
//

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
