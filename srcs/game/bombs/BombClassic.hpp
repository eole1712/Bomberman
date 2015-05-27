#ifndef BOMBCLASSIC_H_
# define BOMBCLASSIC_H_

# include "IBomb.hpp"
# include "IObject.hpp"
# include "Map.hpp"

namespace Bomberman
{

namespace Bomb
{

class Classic
  : public IBomb, public IObject
{
public:
  Classic();
  ~Classic();

private:
  Classic(const Classic &);
  Classic &operator=(const Classic &);

public:
  virtual int		getDuration() const;
  virtual IBomb::Type	getBombType() const;

public:
  virtual void		explose(unsigned int, unsigned int, Map *) const;

public:
  virtual IObject::Type	getObjectType() const;
  virtual bool		isNull() const;
};

}
}

#endif /* !BOMBCLASSIC_H_ */
