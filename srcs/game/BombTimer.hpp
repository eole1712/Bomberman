#ifndef BOMBTIMER_H_
# define BOMBTIMER_H_

# include "Timer.hpp"
# include "IObject.hpp"
# include "Player.hpp"
# include "IBomb.hpp"

namespace Bomberman
{

class BombTimer
  : public IObject, public Timer
{
public:
  BombTimer(IObject *, unsigned int, IBomb *);
  virtual ~BombTimer();

private:
  BombTimer(const BombTimer &);
  BombTimer &operator=(const BombTimer &);

public:
  unsigned int	getRange() const;
  IObject*	getPlayer() const;
  IBomb*	getBombType() const;
  bool		finish(unsigned int x, unsigned int y, Map *map);

private:
  IObject*	_player;
  unsigned int	_range;
  IBomb*	_bomb;

public:
  IObject::Type	getObjectType() const;
  bool		isNull() const;
};

}

#endif /* !BOMBTIMER_H_ */
