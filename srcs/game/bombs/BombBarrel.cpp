#include "IBuff.hpp"
#include "BombBarrel.hpp"
#include "my_random.hpp"

namespace Bomberman
{

namespace Bomb
{

Barrel::Barrel()
{}

Barrel::~Barrel()
{}

int		Barrel::getDuration() const
{
  return 4;
}

Bomb::Type	Barrel::getBombType() const
{
  return Bomb::BARREL;
}

IObject::Type	Barrel::getObjectType() const
{
  return IObject::BARREL;
}

bool		Barrel::isNull() const
{
  return false;
}

void		Barrel::explose(int x, int y, Map *map, unsigned int range, Player *player) const
{
  map->getRcs()->getBomb(CLASSIC)->explose(x, y, map, range, player);

  if (map->getCellValue(x, y)->getObjectType() == IObject::FIRE)
    dynamic_cast<Fire*>(map->getCellValue(x, y))->reset(10000000);

  for (struct {int x; int y; unsigned int r;} s = {x - 1, y - 1, 1};
       s.x >= 0 && s.y >= 0 && s.r < range;
       --s.x, --s.y, ++s.r)
    {
      if (exploseCase(map, s.x, s.y, s.r, player, x, y))
  	break;
    }
  for (struct {int x; int y; unsigned int r;} s = {x + 1, y + 1, 1};
       s.x < int(map->getWidth()) && s.y < int(map->getHeight()) && s.r < range;
       ++s.x, ++s.y, ++s.r)
    {
      if (exploseCase(map, s.x, s.y, s.r, player, x, y))
  	break;
   }
  for (struct {int x; int y; unsigned int r;} s = {x - 1, y + 1, 1};
       s.x >= 0 && s.y < int(map->getHeight()) && s.r < range;
       --s.x, ++s.y, ++s.r)
    {
      if (exploseCase(map, s.x, s.y, s.r, player, x, y))
  	break;
    }
  for (struct {int x; int y; unsigned int r;} s = {x + 1, y - 1, 1};
       s.x < int(map->getWidth()) && s.y >= 0 && s.r < range;
       ++s.x, --s.y, ++s.r)
    {
      if (exploseCase(map, s.x, s.y, s.r, player, x, y))
  	break;
    }
}

void		Barrel::setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					   int y, unsigned int range) const
{
  realMap->getRcs()->getBomb(CLASSIC)->setBlastRangeToMap(map, realMap, x, y, range);
  for (struct {int x; int y; unsigned int r;} s = {x - 1, y - 1, 1};
       s.x >= 0 && s.y >= 0 && s.r < range;
       --s.x, --s.y, ++s.r)
    {
      if (realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(s.x, s.y, AI::UNSAFE);
    }
  for (struct {int x; int y; unsigned int r;} s = {x + 1, y + 1, 1};
       s.x < int(map->getWidth()) && s.y < int(map->getHeight()) && s.r < range;
       ++s.x, ++s.y, ++s.r)
    {
      if (realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(s.x, s.y, AI::UNSAFE);
   }
  for (struct {int x; int y; unsigned int r;} s = {x - 1, y + 1, 1};
       s.x >= 0 && s.y < int(map->getHeight()) && s.r < range;
       --s.x, ++s.y, ++s.r)
    {
      if (realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(s.x, s.y, AI::UNSAFE);
    }
  for (struct {int x; int y; unsigned int r;} s = {x + 1, y - 1, 1};
       s.x < int(map->getWidth()) && s.y >= 0 && s.r < range;
       ++s.x, --s.y, ++s.r)
    {
      if (realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  realMap->getCellValue(s.x, s.y)->getObjectType() == IObject::WALL)
	break;
      map->setCellValue(s.x, s.y, AI::UNSAFE);
    }
}

IBomb*		Barrel::clone() const
{
  return new Barrel;
}

std::string	Barrel::getClassName() const
{
  return "Barrel";
}

}

}
