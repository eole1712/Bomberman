#ifndef __BUFFNOBOMB_HPP__
# define __BUFFNOBOMB_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class NoBomb : public IBuff, public IObject
  {
  public:
    NoBomb();
    ~NoBomb();

  private:
    NoBomb(NoBomb const& other);
    NoBomb&		operator=(NoBomb const& other);

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

#endif /* !__BUFFNOBOMB_HPP__ */
