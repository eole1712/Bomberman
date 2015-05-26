#ifndef DESTROYABLEWALL_H_
# define DESTROYABLEWALL_H_

# include "IObject.hpp"

namespace Bomberman
{

class DestroyableWall
  : public IObject
{
public:
  DestroyableWall();
  virtual ~DestroyableWall();

private:
  DestroyableWall(const DestroyableWall &);
  DestroyableWall &operator=(const DestroyableWall &);

public:
  virtual IObject::Type	getObjectType() const;
  virtual bool		isNull() const;
};
}

#endif /* !DESTROYABLEWALL_H_ */
