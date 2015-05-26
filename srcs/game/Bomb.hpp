#ifndef BOMB_H_
# define BOMB_H_

# include "Timer.hpp"
# include "IObject.hpp"
# include "Player.hpp"

namespace Bomberman
{

class Bomb
  : public IObject, public Timer
{
public:
  Bomb(IObject *, unsigned int);
  virtual ~Bomb();

private:
  Bomb(const Bomb &);
  Bomb &operator=(const Bomb &);

public:
  unsigned int	getRange() const;
  IObject*	getPlayer() const;

private:
  IObject	*_player;
  unsigned int	_range;
};

}

#endif /* !BOMB_H_ */
