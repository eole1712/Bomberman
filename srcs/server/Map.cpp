#include <string>
#include "Map.hpp"

Map::Map(std::string name, std::pair<unsigned int, unsigned int> dimensions)
  : _name(name), _dimensions(dimensions)
{}

Map::~Map()
{}

std::string	Map::getName() const
{
  return (this->_name);
}

std::pair<unsigned int, unsigned int>	Map::getDimensions() const
{
  return (this->_dimensions);
}

IObject*	getCell(std::pair<unsigned int, unsigned int> dimensions) const
{
  return (this->_map[dimensions]);
}

void	Map::setName(std::string name)
{
  this->_name = name;
}

void	Map::setCell(std::pair<unsigned int, unsigned int> dimensions, IObject* obj)
{
  this->_map[dimensions] = obj;
}
