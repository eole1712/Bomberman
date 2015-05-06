#ifndef __IBUFF_HPP__
# define __IBUFF_HPP__

namespace Bomberman
{

class IBuff
{
public:
  enum BuffType
    {
      INC_SPEED,
      DEC_SPEED,
      BOMB,
      NO_ATTACK,
      SHIELD
    };

public:
  virtual ~Buff() {}

public:
  unsigned int	getDuration() const = 0;
  BuffType	getType() const = 0;
  bool		isBonus() const = 0;
  bool		isMalus() const = 0;
};

}

#endif /* !__IBUFF_HPP__ */
