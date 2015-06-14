#ifndef PLAYER_H_
# define PLAYER_H_

# include <string>
# include <list>
# include "Asset3d.hpp"
# include "IObject.hpp"
# include "IBuff.hpp"
# include "BuffTimer.hpp"
# include "BombTypes.hpp"
# include "Object3d.hpp"
# include "glm/glm.hpp"
# include "Animation.hpp"
# include "Score.hpp"
# include "ScoreList.hpp"

namespace Bomberman
{

class Map;

class Player
  : public IObject, public Object3d
{
public:
  Player(std::string const &, glm::vec4);
  Player();
  virtual ~Player();

  void			init();

private:
  Player&		operator=(const Player &);

public:
  typedef void (Player::*Buff_exec)();

public:
  std::string const&	getName() const;
  unsigned int		getRange() const;
  float			getSpeed() const;

private:
  std::string		_name;

public:
  bool			isAlive() const;
  bool			isParalyzed() const;
  bool			zeroBomb() const;
  bool			canAbsorb() const;
  bool			isPlaced() const;
  virtual bool		isIA() const;

private:
  bool			_isAlive;
  bool			_isParalyzed;
  bool			_zeroBomb;
  bool			_isPlaced;

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
  unsigned int		getNbBomb() const;

private:
  unsigned int		_bomb;
  static const unsigned int dftBomb;

public:
  bool			getPutBombStatus() const;
  void			setPutBombStatus(bool status);

private:
  bool			_putBombStatus;

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
  bool			rotate(bool const & direction,
			       float const & elsapsedTime, float const & stop);
  void			rotate(bool const & direction,
			       float const & elsapsedTime);

public:
  void			setBombType(Bomb::Type);
  Bomb::Type		getBombType() const;
  void			putBomb();
  void			putTimedBomb(unsigned int, unsigned int);
  bool			tryToKill();
  void			randWeapon();

private:
  Bomb::Type		_bombType;
  static const Bomb::Type dftBombType;

public:
  glm::vec4		_color;

public:
  void			setColor(glm::vec4 color);
  glm::vec4		getColor() const;

public:
  Score			_score;
  ScoreList*		_scoreList;

public:
  Score			getScore() const;
  void			incScore();
  void			linkScoreList(ScoreList*);

public:
  virtual Type		getObjectType() const;
  virtual bool		isNull() const;

protected:
  Map			*_map;

public:
  Animation		*animation;

  void			draw(Asset3d & asset,
			     gdl::BasicShader & shader,
			     gdl::Clock const & clock) const;
  glm::vec3		getNewPos(Player const *) const;
  glm::vec3		getAbsVec(Player const *sec) const;

public:
  int			getId() const;
  void			setId(int);

private:
  int			_id;


};

}

#endif /* !PLAYER_H_ */
