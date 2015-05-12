#ifndef __BUFFPARALYZED_HPP__
# define __BUFFPARALYZED_HPP__

# include "IBuff.hpp"
# include "IObject.hpp"

namespace Bomberman
{
namespace Buff
{
  class Paralyzed : public IBuff, public Map::IObject
  {
  public:
    Paralyzed();
    ~Paralyzed();

  private:
    Paralyzed(Paralyzed const& other);
    Paralyzed&		operator=(Paralyzed const& other);

  public:
    virtual int			getDuration() const;
    virtual IBuff::Type		getBuffType() const;
    virtual bool		isBonus() const;
    virtual bool		isMalus() const;

  public:
    virtual IBuff*		clone() const;
    virtual std::string		getClassName() const;

  public:
    virtual Map::IObject::Type	getObjectType() const;
  };
}
}

#endif /* !__BUFFPARALYZED_HPP__ */
