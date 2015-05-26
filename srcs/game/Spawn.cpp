#include "Spawn.hpp"

namespace Bomberman
{

Spawn::Spawn()
{

}

Spawn::~Spawn()
{

}

IObject::Type	Spawn::getObjectType() const
{
  return IObject::SPAWN;
}

bool		Spawn::isNull() const
{
  return false;
}

}
