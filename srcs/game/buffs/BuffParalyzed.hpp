#ifndef __BUFFPARALYZED_HPP__
# define __BUFFPARALYZED_HPP__

# include "IBuff.hpp"

namespace Bomberman
{
namespace Buff
{
  class Paralyzed : public IBuff
  {
  public:
    Paralyzed();
    ~Paralyzed();

  private:
    Paralyzed(Paralyzed const& other);
    Paralyzed&		operator=(Paralyzed const& other);

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

#endif /* !__BUFFPARALYZED_HPP__ */
