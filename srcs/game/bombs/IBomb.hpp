#ifndef IBOMB_H_
# define IBOMB_H_

# include "IObject.hpp"
# include "IClonable.hpp"

namespace Bomberman
{

class Map;
class Player;

class IBomb : public IClonable<IBomb>, public IObject
{
public:
  enum Type
    {
      CLASSIC = 0,
      VIRUS,
      MINE
    };

public:
  virtual ~IBomb() {}

public:
  virtual int		getDuration() const = 0;
  virtual Type		getBombType() const = 0;
  virtual void		explose(int, int, Map *, unsigned int, Player*) const = 0;
  static bool		isOtherBomb(Map*, int, int, Player*, int, int);
  static bool		isOtherBomb(Map*, int, int, Player*, int, int, float);

public:
  static const int	nbBomb;
};

}

#endif /* !IBOMB_H_ */
