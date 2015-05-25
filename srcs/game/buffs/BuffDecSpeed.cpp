# include "BuffDecSpeed.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  DecSpeed::DecSpeed()
  {
  }

  DecSpeed::~DecSpeed()
  {
  }

  /*
  ** Public member functions
  */
  int			DecSpeed::getDuration() const
  {
    return (15);
  }

  IBuff::Type		DecSpeed::getBuffType() const
  {
    return (DEC_SPEED);
  }

  bool			DecSpeed::isBonus() const
  {
    return (false);
  }

  bool			DecSpeed::isMalus() const
  {
    return (true);
  }

  IBuff*		DecSpeed::clone() const
  {
    return (new DecSpeed());
  }

  std::string		DecSpeed::getClassName() const
  {
    return ("DecSpeed");
  }

  IObject::Type	DecSpeed::getObjectType() const
  {
    return (IObject::BONUS);
  }

bool			DecSpeed::isNull() const
{
  return false;
}
}
}
