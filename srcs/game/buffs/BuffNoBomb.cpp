# include "BuffNoBomb.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  NoBomb::NoBomb()
  {
  }

  NoBomb::~NoBomb()
  {
  }

  /*
  ** Public member functions
  */
  int			NoBomb::getDuration() const
  {
    return (5);
  }

  IBuff::Type		NoBomb::getBuffType() const
  {
    return (NO_BOMB);
  }

  bool			NoBomb::isBonus() const
  {
    return (false);
  }

  bool			NoBomb::isMalus() const
  {
    return (true);
  }

  IBuff*		NoBomb::clone() const
  {
    return (new NoBomb());
  }

  std::string		NoBomb::getClassName() const
  {
    return ("NoBomb");
  }

  Map::IObject::Type	NoBomb::getObjectType() const
  {
    return (Map::IObject::BONUS);
  }
}
}
