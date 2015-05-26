#ifndef IOBJECT_H_
# define IOBJECT_H_

namespace Bomberman
{

class IObject
{
public:
  enum Type
    {
      BOMB = 0,
      PLAYER,
      BONUS,
      WALL,
      DESTROYABLEWALL,
      EMPTY
    };

public:
  virtual	~IObject() {}

public:
  virtual Type	getObjectType() const = 0;
  virtual bool	isNull() const = 0;
};

}

#endif /* !IOBJECT_H_ */
