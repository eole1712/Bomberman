#include "Empty.hpp"

namespace Bomberman
{

Empty::Empty()
{

}

Empty::~Empty()
{

}

IObject::Type	Empty::getObjectType() const
{
  return IObject::EMPTY;
}

bool		Empty::isNull() const
{
  return true;
}

}
