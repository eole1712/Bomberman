#include <string>
#include "GenericMap.hpp"
#include "Empty.hpp"
#include "Map.hpp"
#include "Player.hpp"

namespace Bomberman
{

Map::Map(std::vector<std::string> players, unsigned int width, unsigned int height)
  : _nbPlayers(players.size()), _players(width * height, NULL), _buffs(7, NULL)
{
  _empty = new Empty;
  setMap(width, height, new IObject*[width*height]);
  initMapToEmpty();
  for (unsigned int i = 0; i < _nbPlayers; i++)
    _players[i] = new Player(players[i], 0, 0);
}

// Map::Map(std::vector<std::string> names, unsigned int width, unsigned int height)
//   : _width(width), _height(height), _nbPlayers(names.size()), _map(width * height, NULL), _players(_nbPlayers, NULL)
// {
//   for (unsigned int i = 0; i < _nbPlayers; i++)
//     {
//       _players[i] = new Player(names[i], 0, 0);
//     }
// }

Map::~Map()
{

}

void		Map::initMapToEmpty()
{
  for (unsigned int x = 0; x < getWidth(); ++x)
    {
      for (unsigned int y = 0; y < getHeight(); ++y)
	setCellValue(x, y, _empty);
    }
}

IObject		*Map::getObject(unsigned int x, unsigned int y) const
{
  return getCellValue(x, y);
}

void		Map::setObject(unsigned int x, unsigned int y, IObject *v)
{
  return setCellValue(x, y, v);
}

void		Map::moveObject(unsigned int xs, unsigned int ys, unsigned int xd, unsigned int yd)
{
  IObject	*obj = getObject(xs, ys);

  setObject(xs, ys, getObject(xd, yd));
  setObject(xd, yd, obj);
}

void		Map::killObject(unsigned int x, unsigned int y)
{
  IObject	*obj = getObject(x, y);

  setObject(x, y, _empty);
  // !!!
  // KILL IT PLEASE
  // !!!
  delete obj;
}

}
