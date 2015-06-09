#include "IBuff.hpp"
#include "my_random.hpp"
#include "IBomb.hpp"
#include "IObject.hpp"
#include "Map.hpp"
#include "Fire.hpp"

namespace Bomberman
{

bool		IBomb::isOtherBomb(Map *map, int x, int y, Player *player, int x2, int y2)
{
  if (map->getCellValue(x, y)->getObjectType() >= IObject::BOMB &&
      !(x == x2 && y == y2))
    {
      dynamic_cast<BombTimer*>(map->getCellValue(x, y))->setFinished();
      return true;
    }
  else
    {
      map->killPlayers(x, y, player);
      map->addFire(player, x, y);
    }
  return false;
}

bool		IBomb::isOtherBomb(Map *map, int x, int y, Player *player, int x2, int y2, float time)
{
  if (map->getCellValue(x, y)->getObjectType() >= IObject::BOMB &&
      !(x == x2 && y == y2))
    {
      dynamic_cast<BombTimer*>(map->getCellValue(x, y))->setFinished();
      return true;
    }
  else
    {
      map->killPlayers(x, y, player);
      map->addFire(player, x, y, time);
    }
  return false;
}


bool		IBomb::exploseCase(Map *map, int x, int y,
				   unsigned int r, Player *player,
				   int x2, int y2)
{
  if (map->getCellValue(x, y)->getObjectType() == IObject::DESTROYABLEWALL ||
      map->getCellValue(x, y)->getObjectType() == IObject::WALL)
    {
      if (map->getCellValue(x, y)->getObjectType() == IObject::DESTROYABLEWALL)
	{
	  int		d = my_random(0, IBuff::prob);

	  if (d < (IBuff::nbBuff + 5))
	    {
	      d = d >= IBuff::nbBuff ? (int)(IBuff::WEAPON) : d;
	      map->setCellValue(x, y, map->getRcs()->getBuff((IBuff::Type)(d)));
	    }
	  else
	    map->addFire(player, x, y, Fire::explosionTime / (r + 1));
	}
      return true;
    }
  isOtherBomb(map, x, y, player, x2, y2, Fire::explosionTime / (r + 1));
  return false;
}

}
