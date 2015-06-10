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
  for (struct {int i; unsigned int r;} s = {x, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (exploseCase(map, s.i, y, s.r, player, x, y))
	break;
    }
  for (unsigned int i = x + 1, r = 1; i < map->getWidth() && r < range; ++i, ++r)
    {
      if (exploseCase(map, i, y, r, player, x, y))
	break;
    }
  for (struct {int i; unsigned int r; } s = {y - 1, 1}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (exploseCase(map, x, s.i, s.r, player, x, y))
	break;
    }
  for (unsigned int i = y + 1, r = 1; i < map->getHeight() && r < range; ++i, ++r)
    {
      if (exploseCase(map, x, i, r, player, x, y))
	break;
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
      if (map->getCellValue(s.i, y) == AI::UNKNOWN || map->getCellValue(s.i, y) == AI::SAFE
	  || map->getCellValue(s.i, y) == AI::BONUS)
	map->setCellValue(s.i, y, AI::UNSAFE);
    }
  for (unsigned int i = x, r = 0; i < map->getWidth() && r < range; ++i, ++r)
    {
      if (realMap->getCellValue(i, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(i, y)->getObjectType() == IObject::WALL)
	break;
      if (map->getCellValue(i, y) == AI::UNKNOWN || map->getCellValue(i, y) == AI::SAFE
	  || map->getCellValue(i, y) == AI::BONUS)
	map->setCellValue(i, y, AI::UNSAFE);
    }
  for (struct {int i; unsigned int r; } s = {y, 0}; s.i >= 0 && s.r < range; --s.i, ++s.r)
    {
      if (realMap->getCellValue(x, s.i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(x, s.i)->getObjectType() == IObject::WALL)
	break;
      if (map->getCellValue(x, s.i) == AI::UNKNOWN || map->getCellValue(x, s.i) == AI::SAFE ||
	  map->getCellValue(x, s.i) == AI::BONUS)
	map->setCellValue(x, s.i, AI::UNSAFE);
    }
  for (unsigned int i = y, r = 0; i < map->getHeight() && r < range; ++i, ++r)
    {
      if (realMap->getCellValue(x, i)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(x, i)->getObjectType() == IObject::WALL)
	break;
      if (map->getCellValue(x, i) == AI::UNKNOWN || map->getCellValue(x, i) == AI::SAFE ||
	  map->getCellValue(x, i) == AI::BONUS)
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
