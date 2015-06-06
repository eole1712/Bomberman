#ifndef PLAYER_H_
# define PLAYER_H_

# include <string>
# include <list>
# include "IObject.hpp"
# include "IBuff.hpp"
# include "BuffTimer.hpp"
# include "IBomb.hpp"
# include "Object3d.hpp"
# include "glm/glm.hpp"
# include "Animation.hpp"

namespace Bomberman
{

class Map;

class Player
  : public IObject, public Object3d
{
public:
  Player(std::string const &, glm::vec4 color);
  Player();
  virtual ~Player();

private:
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
  void			addTimedBuff(BuffTimer*);
  std::list<BuffTimer*> const& getBuffList() const;

private:
  std::list<BuffTimer*>	_buff;
  Buff_exec		_buffOn[8];
  Buff_exec		_buffOff[8];

public:
  void			initGame(unsigned int, unsigned int, Map*);
  void			initGame(Map*);
  unsigned int		getX() const;
  unsigned int		getY() const;
  float			getfX() const;
  float			getfY() const;

protected:
  void			setX(float);
  void			setY(float);

public:
  void			move(float const & direction, float const & elsapsedTime);
  void			rotate(bool const & direction,
			       float const & elsapsedTime, float const & stop);
  void			rotate(bool const & direction,
			       float const & elsapsedTime);


public:
  void			setBombType(IBomb::Type);
  IBomb::Type		getBombType() const;
  void			putBomb();
  void			putTimedBomb(unsigned int, unsigned int);
  bool			tryToKill();
  void			randWeapon();

private:
  IBomb::Type		_bombType;

public:
  glm::vec4		_color;

public:
  void			setColor(glm::vec4 color);
  glm::vec4		getColor() const;

public:
  virtual Type		getObjectType() const;
  virtual bool		isNull() const;

private:
  Map			*_map;

public:
  Animation		*animation;

public:
  // I.A.
  void			moveRight(float const & elsapsedTime);
  void			moveLeft(float const & elsapsedTime);
  void			moveUp(float const & elsapsedTime);
  void			moveDown(float const & elsapsedTime);
};

}

#endif /* !PLAYER_H_ */
