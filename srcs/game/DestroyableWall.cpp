#include "DestroyableWall.hpp"

namespace Bomberman
{

DestroyableWall::DestroyableWall()
{

}

DestroyableWall::~DestroyableWall()
{

}

IObject::Type	DestroyableWall::getObjectType() const
{
  return IObject::DESTROYABLEWALL;
}

bool		DestroyableWall::isNull() const
{
  return false;
}

}
