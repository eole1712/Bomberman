#ifndef __BUFFDECSPEED_HPP__
# define __BUFFDECSPEED_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class DecSpeed : public IBuff, public IObject
  {
  public:
    DecSpeed();
    ~DecSpeed();

  private:
    DecSpeed(DecSpeed const& other);
    DecSpeed&		operator=(DecSpeed const& other);

  public:
    virtual int			getDuration() const;
    virtual IBuff::Type		getBuffType() const;
    virtual bool		isBonus() const;
    virtual bool		isMalus() const;

  public:
    virtual IBuff*		clone() const;
    virtual std::string		getClassName() const;

  public:
    virtual IObject::Type	getObjectType() const;
    virtual bool		isNull() const;
  };
}
}

#endif /* !__BUFFDECSPEED_HPP__ */
