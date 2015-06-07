# include "BuffWeapon.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  Weapon::Weapon()
  {
  }

  Weapon::~Weapon()
  {
  }

  /*
  ** Public member functions
  */
  int			Weapon::getDuration() const
  {
    return (infinite);
  }

  IBuff::Type		Weapon::getBuffType() const
  {
    return (WEAPON);
  }

  bool			Weapon::isBonus() const
  {
    return (true);
  }

  bool			Weapon::isMalus() const
  {
    return (false);
  }

  IBuff*		Weapon::clone() const
  {
    return (new Weapon());
  }

  std::string		Weapon::getClassName() const
  {
    return ("Weapon");
  }

  IObject::Type	Weapon::getObjectType() const
  {
    return (IObject::BONUS);
  }

bool			Weapon::isNull() const
{
  return false;
}
}
}
