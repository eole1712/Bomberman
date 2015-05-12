#ifndef __BUFFSHIELD_HPP__
# define __BUFFSHIELD_HPP__

# include "IBuff.hpp"

namespace Bomberman
{
namespace Buff
{
  class Shield : public IBuff
  {
  public:
    Shield();
    ~Shield();

  private:
    Shield(Shield const& other);
    Shield&		operator=(Shield const& other);

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

#endif /* !__BUFFSHIELD_HPP__ */
