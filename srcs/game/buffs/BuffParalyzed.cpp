# include "BuffParalyzed.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  Paralyzed::Paralyzed()
  {
  }

  Paralyzed::~Paralyzed()
  {
  }

  /*
  ** Public member functions
  */
  int			Paralyzed::getDuration() const
  {
    return (3);
  }

  IBuff::Type		Paralyzed::getBuffType() const
  {
    return (PARALYZED);
  }

  bool			Paralyzed::isBonus() const
  {
    return (false);
  }

  bool			Paralyzed::isMalus() const
  {
    return (true);
  }

  IBuff*		Paralyzed::clone() const
  {
    return (new Paralyzed());
  }

  std::string		Paralyzed::getClassName() const
  {
    return ("Paralyzed");
  }

  IObject::Type	Paralyzed::getObjectType() const
  {
    return (IObject::BONUS);
  }

bool		Paralyzed::isNull() const
{
  return false;
}
}
}
