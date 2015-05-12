# include "BuffShield.hpp"

namespace Bomberman
{
namespace Buff
{
  /*
  ** Constructor/Destructor
  */
  Shield::Shield()
  {
  }

  Shield::~Shield()
  {
  }

  /*
  ** Public member functions
  */
  int		Shield::getDuration() const
  {
    return (5);
  }

  IBuff::Type	Shield::getType() const
  {
    return (SHIELD);
  }

  bool		Shield::isBonus() const
  {
    return (true);
  }

  bool		Shield::isMalus() const
  {
    return (false);
  }

  IBuff*	Shield::clone() const
  {
    return (new Shield());
  }

  std::string	Shield::getClassName() const
  {
    return ("Shield");
  }
}
}