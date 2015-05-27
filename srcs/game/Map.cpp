#include <string>
#include "my_random.hpp"
#include "InvalidNbPlayers.hpp"
#include "InvalidDimensions.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

void	Map::randomize(RessourceStock const& objects)
{
  unsigned int	x;
  unsigned int	y = 0;
  unsigned int	numJoueur = 0;
  unsigned int	playerspace = this->_width * this->_height / this->_nbJoueurs;
  unsigned int	save;

  #include <iostream>
  std::cout << "height : " << this->_height << std::endl;
  std::cout << "width : " << this->_width << std::endl;
  while (y < this->_height)
    {
      x = 0;
      while (x < this->_width)
	{
	  if (y == 0 || y == (this->_height - 1)
	      || x == 0 || x == (this->_width - 1)
	      || my_random(1, 10) > this->_difficulty)
	    this->setCellValue(x, y, objects.getObject(IObject::DESTROYABLEWALL));
	  else
	    {
	      this->setCellValue(x, y, objects.getObject(IObject::WALL));
	      if (++x != this->_width)
		this->setCellValue(x, y, objects.getObject(IObject::DESTROYABLEWALL));
	    }
	  ++x;
	}
      ++y;
    }
  std::cout << "-->" << _nbJoueurs << std::endl;
  while (numJoueur < this->_nbJoueurs)
    {
      std::cout << "Player " << numJoueur << " from " << _nbJoueurs << std::endl;
      save = numJoueur * playerspace + playerspace / 2;
      x = save % this->_width;
      y = save / this->_width;
      this->setCellValue(x, y, objects.getObject(IObject::SPAWN));
      setCellValue(x + (((x > 0 && my_random(0, 1)) || x == _width - 1) ? (-1) : (1)), y,
		   objects.getObject(IObject::EMPTY));
      setCellValue(x, y + (((y > 0 && my_random(0, 1)) || y == _height - 1) ? (-1) : (1)),
		   objects.getObject(IObject::EMPTY));
      ++numJoueur;
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
  std::cout << "-->" << _rcs->getNbPlayer() << std::endl;
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

bool		Map::isIn(unsigned int x, unsigned int y)
{
  return (x < getHeight() && y < getWidth());
}

void		Map::killPlayers(unsigned int x, unsigned int y)
{
  for (unsigned int i = 0; i < _rcs->getNbPlayer(); i++)
    {
      if (dynamic_cast<Player*>(_rcs->getPlayer(i))->getX() == x &&
	  dynamic_cast<Player*>(_rcs->getPlayer(i))->getY() == y)
	dynamic_cast<Player*>(_rcs->getPlayer(i))->tryToKill();
    }
}

void		Map::checkBombsOnMap()
{
  BombTimer	*bomb;

  for (unsigned int y = 0; y < getHeight(); ++y)
    {
      for (unsigned int x; x < getWidth(); ++x)
	{
	  if (getCellValue(x, y)->getObjectType() == IObject::BOMB)
	    {
	      bomb = dynamic_cast<BombTimer*>(getCellValue(x, y));
	      bomb->finish(x, y, this);
	      killObject(x, y);
	      delete bomb;
	    }
	}
    }
}

}
