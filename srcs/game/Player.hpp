#ifndef PLAYER_H_
# define PLAYER_H_

# include <string>
# include <list>
# include "IObject.hpp"
# include "buffs/IBuff.hpp"
# include "BuffTimer.hpp"


namespace Bomberman
{

class Player
  : public IObject
{
public:
  Player(std::string const &, unsigned int, unsigned int);
  virtual ~Player();

private:
  Player(const Player &);
  Player&		operator=(const Player &);

public:
  typedef void (Player::*Buff_exec)();

public:
  std::string const&	getName() const;
  unsigned int		getRange() const;
  unsigned int		getSpeed() const;

private:
  std::string		_name;

public:
  bool			isAlive() const;
  bool			isParalyzed() const;
  bool			zeroBomb() const;
  bool			canAbsorb() const;

private:
  bool			_isAlive;
  bool			_isParalyzed;
  bool			_zeroBomb;

public:
  void			incRange();
  void			decRange();
  void			resetRange();

private:
  unsigned int		_range;
  static const
  unsigned int		dftRange;

public:
  void			incSpeed();
  void			decSpeed();
  void			resetSpeed();

private:
  unsigned int		_speed;
  static const unsigned int dftSpeed;

public:
  void			incShield();
  void			decShield();
  void			resetShield();

private:
  unsigned int		_shield;
  static const unsigned int dftShield;

public:
  void			incBomb();
  void			decBomb();
  void			resetBomb();
  void			enableAttack();
  void			disableAttack();

private:
  unsigned int		_bomb;
  static const unsigned int dftBomb;

public:
  void			paralyze();
  void			unparalyze();

public:
  void			addBuff(IBuff*);
  void			delBuff(IBuff*);
  void			checkBuffList();

private:
  std::list<BuffTimer*>	_buff;
  Buff_exec		_buffOn[7];
  Buff_exec		_buffOff[7];

public:
  void			initPos(unsigned int, unsigned int);
  unsigned int		getX() const;
  unsigned int		getY() const;

private:
  unsigned int		_x;
  unsigned int		_y;

public:
  virtual Type		getObjectType() const;
  virtual bool		isNull() const;
};

}

#endif /* !PLAYER_H_ */
