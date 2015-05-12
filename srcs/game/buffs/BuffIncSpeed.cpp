# include "BuffIncSpeed.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  IncSpeed::IncSpeed()
  {
  }

  IncSpeed::~IncSpeed()
  {
  }

  /*
  ** Public member functions
  */
  int		IncSpeed::getDuration() const
  {
    return (15);
  }

  IBuff::Type	IncSpeed::getType() const
  {
    return (INC_SPEED);
  }

  bool		IncSpeed::isBonus() const
  {
    return (true);
  }

  bool		IncSpeed::isMalus() const
  {
    return (false);
  }

  IBuff*	IncSpeed::clone() const
  {
    return (new IncSpeed());
  }

  std::string	IncSpeed::getClassName() const
  {
    return ("IncSpeed");
  }
}
}
