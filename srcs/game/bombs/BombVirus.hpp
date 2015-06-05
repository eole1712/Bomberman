#ifndef BOMBVIRUS_H_
# define BOMBVIRUS_H_

# include "IBomb.hpp"
# include "IObject.hpp"
# include "Map.hpp"
# include "AIStateMap.hpp"

namespace Bomberman
{

namespace Bomb
{

class Virus
  : public IBomb
{
public:
  Virus();
  ~Virus();

private:
  Virus(const Virus &);
  Virus &operator=(const Virus &);

public:
  virtual int		getDuration() const;
  virtual Bomb::Type	getBombType() const;

public:
  virtual void		explose(int, int, Map *, unsigned int, Player*) const;
  virtual IBomb*	clone() const;
  virtual std::string	getClassName() const;
  virtual void		setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					   int y, unsigned int range) const;

public:
  virtual IObject::Type	getObjectType() const;
  virtual bool		isNull() const;
};

}
}

#endif /* !BOMBVIRUS_H_ */
