//
// IMapObject.hpp for  in /home/ghukas_g/rendu/cpp_bomberman/srcs
//
// Made by Grisha GHUKASYAN
// Login   <ghukas_g@epitech.net>
//
// Started on  Wed May  6 19:39:18 2015 Grisha GHUKASYAN
// Last update Wed May  6 20:48:17 2015 Grisha GHUKASYAN
//

#ifndef IOBJECT_H_
# define IOBJECT_H_

namespace Bomberman
{

namespace Map
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
}

#endif /* !IOBJECT_H_ */
