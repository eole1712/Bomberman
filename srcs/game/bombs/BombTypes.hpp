#ifndef __BOMBTYPES_HPP__
# define __BOMBTYPES_HPP__

namespace Bomberman
{
  namespace Bomb
  {
    enum Type
      {
	CLASSIC = 0,
	VIRUS,
	MINE
      };
    const int	nbBomb = 3;
  }
}

#endif /* !__BOMBTYPES_HPP__ */
