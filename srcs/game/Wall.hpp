#ifndef WALL_H_
# define WALL_H_

# include "IObject.hpp"

namespace Bomberman
{

class Wall
  : public IObject
{
public:
  Wall();
  virtual ~Wall();

private:
  Wall(const Wall &);
  Wall &operator=(const Wall &);

public:
  virtual IObject::Type	getObjectType() const;
  virtual bool		isNull() const;
};
}

#endif /* !WALL_H_ */
