#ifndef __BUFFINCBOMB_HPP__
# define __BUFFINCBOMB_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class IncBomb : public IBuff, public IObject
  {
  public:
    IncBomb();
    ~IncBomb();

  private:
    IncBomb(IncBomb const& other);
    IncBomb&		operator=(IncBomb const& other);

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

#endif /* !__BUFFINCBOMB_HPP__ */
