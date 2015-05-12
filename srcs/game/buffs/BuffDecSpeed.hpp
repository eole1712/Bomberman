#ifndef __BUFFDECSPEED_HPP__
# define __BUFFDECSPEED_HPP__

# include "IBuff.hpp"

namespace Bomberman
{
namespace Buff
{
  class DecSpeed : public IBuff
  {
  public:
    DecSpeed();
    ~DecSpeed();

  private:
    DecSpeed(DecSpeed const& other);
    DecSpeed&		operator=(DecSpeed const& other);

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

#endif /* !__BUFFDECSPEED_HPP__ */
