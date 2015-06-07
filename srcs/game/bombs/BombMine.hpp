#ifndef BOMBMINE_H_
# define BOMBMINE_H_

# include "IBomb.hpp"
# include "IObject.hpp"
# include "Map.hpp"

namespace Bomberman
{

namespace Bomb
{

class Mine
  : public IBomb
{
public:
  Mine();
  ~Mine();

private:
  Mine(const Mine &);
  Mine &operator=(const Mine &);

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

#endif /* !BOMBMINE_H_ */
