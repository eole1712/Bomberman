#ifndef __BUFFINCSPEED_HPP__
# define __BUFFINCSPEED_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class IncSpeed : public IBuff, public IObject
  {
  public:
    IncSpeed();
    ~IncSpeed();

  private:
    IncSpeed(IncSpeed const& other);
    IncSpeed&		operator=(IncSpeed const& other);

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

#endif /* !__BUFFINCSPEED_HPP__ */
