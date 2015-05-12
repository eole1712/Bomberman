#ifndef __BUFFINCSPEED_HPP__
# define __BUFFINCSPEED_HPP__

# include "IBuff.hpp"

namespace Bomberman
{
namespace Buff
{
  class IncSpeed : public IBuff
  {
  public:
    IncSpeed();
    ~IncSpeed();

  private:
    IncSpeed(IncSpeed const& other);
    IncSpeed&		operator=(IncSpeed const& other);

  public:
    virtual int		getDuration() const;
    virtual Type	getType() const;
    virtual bool	isBonus() const;
    virtual bool	isMalus() const;

  public:
    virtual IBuff*	clone() const;
    virtual std::string	getClassName() const;
  };
}
}

#endif /* !__BUFFINCSPEED_HPP__ */
