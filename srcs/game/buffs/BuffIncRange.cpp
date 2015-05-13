# include "BuffIncRange.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  IncRange::IncRange()
  {
  }

  IncRange::~IncRange()
  {
  }

  /*
  ** Public member functions
  */
  int			IncRange::getDuration() const
  {
    return (IBuff::infinite);
  }

  IBuff::Type		IncRange::getBuffType() const
  {
    return (INC_RANGE);
  }

  bool			IncRange::isBonus() const
  {
    return (true);
  }

  bool			IncRange::isMalus() const
  {
    return (false);
  }

  IBuff*		IncRange::clone() const
  {
    return (new IncRange());
  }

  std::string		IncRange::getClassName() const
  {
    return ("IncRange");
  }

  IObject::Type	IncRange::getObjectType() const
  {
    return (IObject::BONUS);
  }
}
}
