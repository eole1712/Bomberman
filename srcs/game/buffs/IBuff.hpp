#ifndef __IBUFF_HPP__
# define __IBUFF_HPP__

# include "IClonable.hpp"

namespace Bomberman
{
  class IBuff : public IClonable
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
    virtual ~IBuff() {}

  public:
    virtual unsigned int	getDuration() const = 0;
    virtual BuffType		getType() const = 0;
    virtual bool		isBonus() const = 0;
    virtual bool		isMalus() const = 0;
  };
}

#endif /* !__IBUFF_HPP__ */
