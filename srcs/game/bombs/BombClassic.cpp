#include "IBuff.hpp"
#include "BombClassic.hpp"
#include "my_random.hpp"

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

Bomb::Type	Classic::getBombType() const
{
  return Bomb::CLASSIC;
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
  int	        d;

  for (struct {int i; unsigned int r;} s = {x, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (map->getCellValue(s.i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(s.i, y)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(s.i, y)->getObjectType() == IObject::DESTROYABLEWALL)
	    {
	      if ((d = my_random(0, IBuff::prob)) < (IBuff::nbBuff + 5))
	      	{
	      	  d = d >= IBuff::nbBuff ? (int)(IBuff::WEAPON) : d;
	      	  map->setCellValue(s.i, y, map->getRcs()->getBuff((IBuff::Type)(d)));
	      	}
	      else
		map->addFire(player, s.i, y);
	    }
	  break;
	}
      map->killPlayers(s.i, y);
      map->addFire(player, s.i, y);
    }
  for (unsigned int i = x, r = 0; i < map->getWidth() && r < range; ++i, ++r)
    {
      if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i, y)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL)
	    {
	      if ((d = my_random(0, IBuff::prob)) < (IBuff::nbBuff + 5))
	      	{
	      	  d = d >= IBuff::nbBuff ? (int)(IBuff::WEAPON) : d;
		  map->setCellValue(i, y, map->getRcs()->getBuff((IBuff::Type)(d)));
		}
	      else
		map->addFire(player, i, y);
	    }
	  break;
	}
      map->killPlayers(i, y);
      map->addFire(player, i, y);
    }
  for (struct {int i; unsigned int r; } s = {y, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (map->getCellValue(x, s.i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, s.i)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(x, s.i)->getObjectType() == IObject::DESTROYABLEWALL)
	    {
	      if ((d = my_random(0, IBuff::prob)) < (IBuff::nbBuff + 5))
	      	{
	      	  d = d >= IBuff::nbBuff ? (int)(IBuff::WEAPON) : d;
		  map->setCellValue(x, s.i, map->getRcs()->getBuff((IBuff::Type)(d)));
		}
	      else
		map->addFire(player, x, s.i);
	    }
	  break;
	}
      map->killPlayers(x, s.i);
      map->addFire(player, x, s.i);
    }
  for (unsigned int i = y, r = 0; i < map->getHeight() && r < range; ++i, ++r)
    {
      if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i)->getObjectType() == IObject::WALL)
	{
	  if (map->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL)
	    {
	      if ((d = my_random(0, IBuff::prob)) < (IBuff::nbBuff + 5))
	      	{
	      	  d = d >= IBuff::nbBuff ? (int)(IBuff::WEAPON) : d;
		  map->setCellValue(x, i, map->getRcs()->getBuff((IBuff::Type)(d)));
		}
	      else
		map->addFire(player, x, i);
	    }
	  break;
	}
      map->killPlayers(x, i);
      map->addFire(player, x, i);
    }
}

  void		Classic::setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					    int y, unsigned int range) const
  {
  for (struct {int i; unsigned int r;} s = {x, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (realMap->getCellValue(s.i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(s.i, y)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(s.i, y, AI::UNSAFE);
    }
  for (unsigned int i = x, r = 0; i < map->getWidth() && r < range; ++i, ++r)
    {
      if (realMap->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(i, y)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(i, y, AI::UNSAFE);
    }
  for (struct {int i; unsigned int r; } s = {y, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (realMap->getCellValue(x, s.i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(x, s.i)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(x, s.i, AI::UNSAFE);
    }
  for (unsigned int i = y, r = 0; i < map->getHeight() && r < range; ++i, ++r)
    {
      if (realMap->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(x, i)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(x, i, AI::UNSAFE);
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
