#ifndef IOBJECT_H_
# define IOBJECT_H_

namespace Bomberman
{

class IObject
{
public:
  enum Type
    {
      BOMB,
      PLAYER,
      BONUS,
      WALL,
      DESTROYABLEWALL
    };

public:
  virtual	~IObject() {}

public:
  virtual Type	getObjectType() const = 0;
};

}

#endif /* !IOBJECT_H_ */
