#include <string>
#include "RessourceStock.hpp"
#include "Map.hpp"

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
	    this->setCellValue(x, y, objects.getUndestroyableWall());
	  else
	    this->setCellValue(x, y, objects.getWall());
	  ++x;
	}
      ++y;
    }
  while (numJoueur >= this->_nbJoueurs)
    {
      save = numJoueur * ratio + my_random(0, 2);
      x = save % this->_height;
      y = save / this->_height;
      this->setCellValue(x, y, objects.getEmpty());
      this->setCellValue(x + ((my_random(0, 1) == 0) ? (1) : (-1)), y, objects.getEmpty());
      this->setCellValue(x, y + ((my_random(0, 1) == 0) ? (1) : (-1)), objects.getEmpty());
    }
}

Map::Map(std::string name, unsigned int width, unsigned int height,
	 unsigned int nbJoueurs, e_difficulty difficulty,
	 RessourceStock const& objects)
  : _name(name), _width(width), _height(height), _nbJoueurs(nbJoueurs),
    _difficulty(difficulty)
{
  if (this->_nbJoueurs == 0
      || this->_width * this->_height / this->_nbJoueurs < 4)
    throw new InvalidNbPlayers();
  if (this->_height < 5 || this->_width < 5)
    throw new InvalidDimensions();
  this->randomize(objects);
  // check aucun endroit inaccessible
}
