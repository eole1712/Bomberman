#include "IBomb.hpp"
#include "IObject.hpp"
#include "Map.hpp"

namespace Bomberman
{

const int	IBomb::nbBomb = 3;

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
      map->killPlayers(x, y);
      map->addFire(player, x, y);
    }
  return false;
}

}
