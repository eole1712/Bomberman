//
// Player.hpp for  in /home/ghukas_g/rendu/cpp_bomberman/srcs
//
// Made by Grisha GHUKASYAN
// Login   <ghukas_g@epitech.net>
//
// Started on  Wed May  6 19:57:54 2015 Grisha GHUKASYAN
// Last update Thu May  7 16:32:33 2015 Grisha GHUKASYAN
//

#ifndef PLAYER_H_
# define PLAYER_H_

# include <string>
# include <list>
# include "IObject.hpp"
# include "buffs/IBuff.hpp"

namespace Bomberman
{

class Player
  : public Map::IObject
{
public:
  Player(std::string const &);
  virtual ~Player();

private:
  Player(const Player &);
  Player&		operator=(const Player &);

public:
  std::string const&	getName() const;
  unsigned int		getRange() const;
  unsigned int		getSpeed() const;

private:
  std::string		_name;

public:
  void			incRange();
  void			decRange();
  void			resetRange();

private:
  unsigned int		_range;
  static const
  unsigned int		defRange;

public:
  void			incSpeed();
  void			decSpeed();
  void			resetSpeed();

private:
  unsigned int		_speed;
  static const unsigned int defSpeed;

public:
  bool			isAlive() const;

private:
  bool			_isAlive;

public:
  void			addBuff(IBuff *);
  void			delBuff(IBuff *);
  void			checkBuffList();

private:
  std::list<IBuff*>	_buff;
};

}

#endif /* !PLAYER_H_ */
