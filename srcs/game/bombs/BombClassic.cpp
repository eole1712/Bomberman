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

void		Classic::explose(int x, int y, Map *map, unsigned int range, Player *player) const
{
  Fire		*fire;

  for (struct {int i; unsigned int r;} s = {x, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (map->getCellValue(s.i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(s.i, y)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(s.i, y)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(s.i, y);
	  break;
	}
      map->killPlayers(s.i, y);
      fire = new Fire(player, s.i, y);
      map->setCellValue(s.i, y, fire);
      map->addFire(fire);
    }
  for (unsigned int i = x, r = 0; i < map->getWidth() && r < range; ++i, ++r)
    {
      if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i, y)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(i, y);
	  break;
	}
      map->killPlayers(i, y);
      fire = new Fire(player, i, y);
      map->setCellValue(i, y, fire);
      map->addFire(fire);
    }
  for (struct {int i; unsigned int r; } s = {y, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (map->getCellValue(x, s.i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, s.i)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(x, s.i)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(x, s.i);
	  break;
	}
      map->killPlayers(x, s.i);
      fire = new Fire(player, x, s.i);
      map->setCellValue(x, s.i, fire);
      map->addFire(fire);
    }
  for (unsigned int i = y, r = 0; i < map->getHeight() && r < range; ++i, ++r)
    {
      if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL)
	    map->killObject(x, i);
	  break;
	}
      map->killPlayers(x, i);
      fire = new Fire(player, x, i);
      map->setCellValue(x, i, fire);
      map->addFire(fire);
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
