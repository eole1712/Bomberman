#ifndef IBOMB_H_
# define IBOMB_H_

# include "IObject.hpp"
# include "IClonable.hpp"
# include "AIStateMap.hpp"
# include "BombTypes.hpp"

namespace Bomberman
{

class Map;
class Player;

namespace AI
{
class StateMap;
}

class IBomb : public IClonable<IBomb>, public IObject
{
public:
  virtual ~IBomb() {}

public:
  virtual int		getDuration() const = 0;
  virtual Bomb::Type	getBombType() const = 0;
  virtual void		explose(int, int, Map *, unsigned int, Player*) const = 0;
  virtual void		setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					   int y, unsigned int range) const = 0;
};

}

#endif /* !IBOMB_H_ */
