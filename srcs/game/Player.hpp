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
  template<enum IBuff::Type>
  void			execBuff(IBuff *);
  void			addBuff(IBuff *);
  void			delBuff(IBuff *);
  void			checkBuffList();

private:
  std::list<IBuff*>	_buff;

private:
  unsigned int		_putBomb;
  unsigned int		_maxBomb;
};

template <>
void			Player::execBuff<IBuff::INC_SPEED>(IBuff *);
template <>
void			Player::execBuff<IBuff::DEC_SPEED>(IBuff *);
template <>
void			Player::execBuff<IBuff::INC_BOMB>(IBuff *);
template <>
void			Player::execBuff<IBuff::NO_BOMB>(IBuff *);
template <>
void			Player::execBuff<IBuff::PARALYZED>(IBuff *);
template <>
void			Player::execBuff<IBuff::SHIELD>(IBuff *);

}

#endif /* !PLAYER_H_ */
