#ifndef __BUFFWEAPON_HPP__
# define __BUFFWEAPON_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class Weapon : public IBuff
  {
  public:
    Weapon();
    ~Weapon();

  private:
    Weapon(Weapon const& other);
    Weapon&		operator=(Weapon const& other);

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

#endif /* !__BUFFWEAPON_HPP__ */
