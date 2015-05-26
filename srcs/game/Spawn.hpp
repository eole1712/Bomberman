#ifndef SPAWN_H_
# define SPAWN_H_

# include "IObject.hpp"

namespace Bomberman
{

class Spawn
  : public IObject
{
public:
  Spawn();
  virtual ~Spawn();

private:
  Spawn(const Spawn &);
  Spawn &operator=(const Spawn &);

public:
  virtual IObject::Type	getObjectType() const;
  virtual bool		isNull() const;
};
}

#endif /* !SPAWN_H_ */
