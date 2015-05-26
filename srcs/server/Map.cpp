#include <string>
#include "RessourceStock.hpp"
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
  unsigned int	numJoueur = 1;
  unsigned int	ratio = this->_width * this->_height / this->_nbJoueurs;
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
  while (numJoueur >= this->_nbJoueurs)
    {
      save = numJoueur * ratio + my_random(0, 2);
      x = save % this->_height;
      y = save / this->_height;
      this->setCellValue(x, y, objects.getObject(IObject::EMPTY));
      this->setCellValue(x + ((my_random(0, 1) == 0) ? (1) : (-1)), y,
			 objects.getObject(IObject::EMPTY));
      this->setCellValue(x, y + ((my_random(0, 1) == 0) ? (1) : (-1)),
			 objects.getObject(IObject::EMPTY));
    }
}

Map::Map(std::string name, unsigned int width, unsigned int height,
	 unsigned int nbJoueurs, e_difficulty difficulty,
	 RessourceStock const& objects)
  : GenericMap<IObject*>(width, height), _name(name),
  _nbJoueurs(nbJoueurs), _difficulty(difficulty)
{
  this->_width = width;
  this->_height = height;
  if (this->_nbJoueurs == 0
      || this->_width * this->_height / this->_nbJoueurs < 4)
    throw new Exception::InvalidNbPlayers("Map Constructor");
  if (this->_height < 5 || this->_width < 5)
    throw new Exception::InvalidDimensions("Map Constructor");
  this->randomize(objects);
  // check aucun endroit inaccessible
}

}
