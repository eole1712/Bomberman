#ifndef __BUFFINCRANGE_HPP__
# define __BUFFINCRANGE_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class IncRange : public IBuff
  {
  public:
    IncRange();
    ~IncRange();

  private:
    IncRange(IncRange const& other);
    IncRange&		operator=(IncRange const& other);

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

#endif /* !__BUFFINCRANGE_HPP__ */
