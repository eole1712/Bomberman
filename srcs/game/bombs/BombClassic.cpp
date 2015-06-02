#include "BombClassic.hpp"

namespace Bomberman
{

namespace Bomb
{

Classic::Classic()
{}

Classic::~Classic()
{}

int		Classic::getDuration() const
{
  return 3;
}

IBomb::Type	Classic::getBombType() const
{
  return IBomb::CLASSIC;
}

IObject::Type	Classic::getObjectType() const
{
  return IObject::BOMB;
}

bool		Classic::isNull() const
{
  return false;
}

void		Classic::explose(unsigned int x, unsigned int y, Map *map) const
{
  for (int i = x; i >= 0; --i)
    {
      if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i, y)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(i, y);
	  break;
	}
      map->killPlayers(i, y);
    }
  for (unsigned int i = x; i < map->getWidth(); ++i)
    {
      if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i, y)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(i, y);
	  break;
	}
      map->killPlayers(i, y);
    }
  for (int i = y; i >= 0; --i)
    {
      if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(x, i);
	  break;
	}
      map->killPlayers(x, i);
    }
  for (unsigned int i = y; i < map->getHeight(); ++i)
    {
      if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(x, i);
	  break;
	}
      map->killPlayers(x, i);
    }
}

IBomb*		Classic::clone() const
{
  return new Classic;
}

std::string	Classic::getClassName() const
{
  return "Classic";
}

}

}
