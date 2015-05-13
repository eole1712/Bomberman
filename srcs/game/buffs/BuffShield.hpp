#ifndef __BUFFSHIELD_HPP__
# define __BUFFSHIELD_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class Shield : public IBuff, public IObject
  {
  public:
    Shield();
    ~Shield();

  private:
    Shield(Shield const& other);
    Shield&		operator=(Shield const& other);

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
  };
}
}

#endif /* !__BUFFSHIELD_HPP__ */
