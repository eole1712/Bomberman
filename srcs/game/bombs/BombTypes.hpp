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
	MINE,
	BARREL
      };
    const int	nbBomb = 4;
  }
}

#endif /* !__BOMBTYPES_HPP__ */
