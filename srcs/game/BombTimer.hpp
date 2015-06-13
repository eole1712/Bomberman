#ifndef BOMBTIMER_H_
# define BOMBTIMER_H_

# include "Timer.hpp"
# include "IObject.hpp"
# include "Player.hpp"
# include "IBomb.hpp"
# include "AIStateMap.hpp"

namespace Bomberman
{

  class IBomb;

namespace AI
{
  class StateMap;
}

class BombTimer
  : public IObject, public Timer
{
public:
  BombTimer(Player *, unsigned int, IBomb *);
  BombTimer(Player *, unsigned int, IBomb *, float, unsigned int x, unsigned int y, bool isVirus);
  virtual ~BombTimer();

private:
  BombTimer(const BombTimer &);
  BombTimer &operator=(const BombTimer &);

public:
  unsigned int	getRange() const;
  Player*	getPlayer() const;
  IBomb*	getBombType() const;
  bool		finish(unsigned int x, unsigned int y, Map *map);
  void		setBlastRangeToMap(AI::StateMap* map, Map const* realMap) const;

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
  void		setFinished();

private:
  bool		_isFinished;
  bool		_isVirus;

public:
  IObject::Type	getObjectType() const;
  bool		isNull() const;
};

}

#endif /* !BOMBTIMER_H_ */
