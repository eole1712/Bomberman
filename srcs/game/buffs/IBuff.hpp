#ifndef __IBUFF_HPP__
# define __IBUFF_HPP__

# include "IClonable.hpp"

namespace Bomberman
{
  class IBuff : public IClonable<IBuff>
  {
  public:
    enum Type
      {
	INC_SPEED = 0,
	DEC_SPEED,
	INC_BOMB,
	INC_RANGE,
	NO_BOMB,
	PARALYZED,
	SHIELD
      };

  public:
    virtual ~IBuff() {}

  public:
    /*
    ** if duration is equals to IBuff::infinite, the buff never disappears
    */
    virtual int		getDuration() const = 0;
    virtual Type	getBuffType() const = 0;
    virtual bool	isBonus() const = 0;
    virtual bool	isMalus() const = 0;

  public:
    static const int	infinite;
    static const int	nbBuff;
  };
}

#endif /* !__IBUFF_HPP__ */
