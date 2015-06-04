#ifndef FIRE_H_
# define FIRE_H_

# include "Timer.hpp"
# include "IObject.hpp"
# include "Player.hpp"
# include "IBomb.hpp"

namespace Bomberman
{

class Fire
  : public IObject, public Timer
{
public:
  Fire(Player *, unsigned int, unsigned int);
  virtual ~Fire();

private:
  Fire(const Fire &);
  Fire &operator=(const Fire &);

public:
  unsigned int	getRange() const;
  Player*	getPlayer() const;
  IBomb*	getBombType() const;

private:
  Player*	_player;
  unsigned int	_range;
  IBomb*	_bomb;

public:
  unsigned int	getX() const;
  unsigned int	getY() const;

private:
  unsigned int	_x;
  unsigned int	_y;

public:
  IObject::Type	getObjectType() const;
  bool		isNull() const;

public:
  static const float	explosionTime;
};

}

#endif /* !FIRE_H_ */
