# include "BuffIncBomb.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  IncBomb::IncBomb()
  {
  }

  IncBomb::~IncBomb()
  {
  }

  /*
  ** Public member functions
  */
  int			IncBomb::getDuration() const
  {
    return (IBuff::infinite);
  }

  IBuff::Type		IncBomb::getBuffType() const
  {
    return (INC_BOMB);
  }

  bool			IncBomb::isBonus() const
  {
    return (true);
  }

  bool			IncBomb::isMalus() const
  {
    return (false);
  }

  IBuff*		IncBomb::clone() const
  {
    return (new IncBomb());
  }

  std::string		IncBomb::getClassName() const
  {
    return ("IncBomb");
  }

  IObject::Type	IncBomb::getObjectType() const
  {
    return (IObject::BONUS);
  }
}
}
