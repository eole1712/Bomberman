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
      SPAWN,
      EMPTY,
      FIRE
    };

public:
  virtual ~IObject() {}

public:
  virtual Type		getObjectType() const = 0;
  virtual bool		isNull() const = 0;

public:
  static const int	nbObject;
};

}

#endif /* !IOBJECT_H_ */
