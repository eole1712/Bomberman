#ifndef __BUFFINCBOMB_HPP__
# define __BUFFINCBOMB_HPP__

# include "IBuff.hpp"

namespace Bomberman
{
namespace Buff
{
  class IncBomb : public IBuff
  {
  public:
    IncBomb();
    ~IncBomb();

  private:
    IncBomb(IncBomb const& other);
    IncBomb&		operator=(IncBomb const& other);

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

#endif /* !__BUFFINCBOMB_HPP__ */
