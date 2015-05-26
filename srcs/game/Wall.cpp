#include "Wall.hpp"

namespace Bomberman
{

Wall::Wall()
{

}

Wall::~Wall()
{

}

IObject::Type	Wall::getObjectType() const
{
  return IObject::WALL;
}

bool		Wall::isNull() const
{
  return false;
}

}
