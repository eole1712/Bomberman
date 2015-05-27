#include <string>
#include "my_random.hpp"
#include "InvalidNbPlayers.hpp"
#include "InvalidDimensions.hpp"
#include "Map.hpp"

namespace Bomberman
{

void	Map::randomize(RessourceStock const& objects)
{
  unsigned int	x;
  unsigned int	y = 0;
  unsigned int	numJoueur = 0;
  unsigned int	playerspace = this->_width * this->_height / this->_nbJoueurs;
  unsigned int	save;

  while (y != this->_height)
    {
      x = 0;
      while (x != this->_width)
	{
	  if (my_random(1, 10) <= this->_difficulty)
	    this->setCellValue(x, y, objects.getObject(IObject::WALL));
	  else
	    this->setCellValue(x, y, objects.getObject(IObject::DESTROYABLEWALL));
	  ++x;
	}
      ++y;
    }
  while (numJoueur < this->_nbJoueurs)
    {
      save = numJoueur * playerspace + playerspace / 2;
      x = save % this->_width;
      y = save / this->_width;
      this->setCellValue(x, y, objects.getObject(IObject::SPAWN));
      setCellValue(x + (((x > 0 && my_random(0, 1)) || x == _width - 1) ? (-1) : (1))
		   , y, objects.getObject(IObject::EMPTY));
      setCellValue(x, y + (((y > 0 && my_random(0, 1)) || y == _height - 1) ? (-1) : (1))
		   , objects.getObject(IObject::EMPTY));
      numJoueur++;
    }
}

Map::Map(std::string name, unsigned int width, unsigned int height,
	 unsigned int nbJoueurs, e_difficulty difficulty,
	 RessourceStock * objects)
  : GenericMap<IObject*>(width, height), _name(name),
    _nbJoueurs(nbJoueurs), _difficulty(difficulty), _rcs(objects)
{
  this->_width = width;
  this->_height = height;
  if (this->_nbJoueurs == 0
      || this->_width * this->_height / this->_nbJoueurs < 4)
    throw new Exception::InvalidNbPlayers("Map Constructor");
  if (this->_height < 5 || this->_width < 5)
    throw new Exception::InvalidDimensions("Map Constructor");
  this->randomize(*objects);
  // check aucun endroit inaccessible
}

void		Map::swapObjects(unsigned int x, unsigned int y, unsigned int nx, unsigned int ny)
{
  IObject	*obj = getCellValue(x, y);

  setCellValue(x, y, getCellValue(nx, ny));
  setCellValue(nx, ny, obj);
}

void		Map::killObject(unsigned int x, unsigned int y)
{
  setCellValue(x, y, _rcs->getObject(IObject::EMPTY));
}

RessourceStock	*Map::getRcs() const
{
  return _rcs;
}

std::string const&	Map::getName() const
{
  return _name;
}

unsigned int		Map::getNumberPlayers() const
{
  return _nbJoueurs;
}

Map::e_difficulty		Map::getDiff() const
{
  return _difficulty;
}

}