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
  dynamic_cast<IBomb*>(map->getRcs()->getBomb(CLASSIC))->explose(x, y, map, range, player);

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
