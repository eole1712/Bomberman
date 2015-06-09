#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "JSONDoc.hpp"
#include "MapList.hpp"

namespace Bomberman
{

MapList::MapList()
{}

MapList::~MapList()
{}

Map*	MapList::getMap(const std::string &name) const
{
  if (_json.parse("./resources/json/" + name + ".json"))
    return (_json.unserialize<Bomberman::Map>(name));
  return (NULL);
}

void	MapList::addMap(Map* map)
{
  this->_maps.insert(map->getName(), std::make_pair(map->getWidth(), map->getHeight()));
}

std::unordered_map<std::string, std::pair<unsigned int, unsigned int> >	MapList::getMapList() const
{
  return (this->_maps);
}

bool	MapList::operator==(MapList const& other) const
{
  return _maps == other._maps;
}

}
