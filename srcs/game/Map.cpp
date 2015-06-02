#include <string>
#include "my_random.hpp"
#include "InvalidNbPlayers.hpp"
#include "InvalidDimensions.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

Map::Map(std::string name, unsigned int width, unsigned int height,
	 unsigned int nbJoueurs, e_difficulty difficulty,
	 RessourceStock* objects)
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
  this->randomize();
  this->equalize();
  // check aucun endroit inaccessible
  this->spawnize();
}

Map::Map(std::string name, unsigned int width, unsigned int height,
	 unsigned int nbJoueurs, e_difficulty difficulty)
  : GenericMap<IObject*>(width, height), _name(name),
    _nbJoueurs(nbJoueurs), _difficulty(difficulty), _rcs(NULL)
{
  this->_width = width;
  this->_height = height;
  if (this->_nbJoueurs == 0
      || this->_width * this->_height / this->_nbJoueurs < 4)
    throw new Exception::InvalidNbPlayers("Map Constructor");
  if (this->_height < 5 || this->_width < 5)
    throw new Exception::InvalidDimensions("Map Constructor");
  //std::cout << "-->" << _rcs->getNbPlayer() << std::endl;
  // check aucun endroit inaccessible
}

void	Map::randomize()
{
  unsigned int	x;
  unsigned int	y = 0;

  while (y < this->_height)
    {
      x = 0;
      while (x < this->_width)
	{
	  if (y == 0 || y == (this->_height - 1)
	      || x == 0 || x == (this->_width - 1)
	      || my_random(1, 10) > this->_difficulty)
	    this->setCellValue(x, y, this->_rcs->getObject(IObject::DESTROYABLEWALL));
	  else
	    this->setCellValue(x, y, this->_rcs->getObject(IObject::WALL));
	  ++x;
	}
      ++y;
    }
}

bool	Map::checkDensity(unsigned int x, unsigned int y)
{
  unsigned int	posx;
  unsigned int	posy = 0;
  unsigned int	i = 0;

  while (posy < 3)
    {
      posx = 0;
      while (posx < 3)
	{
	  i += (this->getCellValue(x + posx, y  + posy)->getObjectType() == IObject::WALL);
	  ++posx;
	}
      ++posy;
    }
  return (!i);
}

void	Map::equalize()
{
  unsigned int	x;
  unsigned int	y = 0;
  unsigned int	radius;

  switch(this->_difficulty)
    {
    case EASY:
      radius = 5;
      break;
    case MEDIUM:
      radius = 4;
      break;
    case DIFFICULT:
      radius = 3;
      break;
    }
  while (y < this->_height)
    {
      x = 0;
      while (x < this->_width)
	{
	  if ((x + radius) < this->_width && (y + radius) < this->_height
	      && this->checkDensity(x, y))
	    {
	      this->setCellValue(x, y, this->_rcs->getObject(IObject::WALL));
	      this->setCellValue(x + radius, y + radius, this->_rcs->getObject(IObject::WALL));
	      x = x + radius;
	    }
	  ++x;
	}
      ++y;
    }
}

void	Map::spawnize()
{
  unsigned int	x;
  unsigned int	y;
  unsigned int	numJoueur = 0;
  unsigned int	playerspace = this->_width * this->_height / this->_nbJoueurs;
  unsigned int	pos;

  while (numJoueur < this->_nbJoueurs)
    {
      pos = numJoueur * playerspace + playerspace / 2;
      x = pos % this->_width;
      y = pos / this->_width;
      this->setCellValue(x, y, this->_rcs->getObject(IObject::SPAWN));
      this->setCellValue(x + (((x > 0 && my_random(0, 1)) || x == _width - 1) ? (-1) : (1)), y,
			 this->_rcs->getObject(IObject::EMPTY));
      this->setCellValue(x, y + (((y > 0 && my_random(0, 1)) || y == _height - 1) ? (-1) : (1)),
			 this->_rcs->getObject(IObject::EMPTY));
      ++numJoueur;
    }
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
      for (unsigned int x = 0; x < getWidth(); ++x)
	{
	  if (getCellValue(x, y)->getObjectType() == IObject::BOMB)
	    {
	      bomb = dynamic_cast<BombTimer*>(getCellValue(x, y));
	      if (bomb->finish(x, y, this))
		{
		  killObject(x, y);
		  delete bomb;
		}
	    }
	}
    }
}

unsigned int		Map::getNumberPlayers() const
{
  return _nbJoueurs;
}

std::string const&	Map::getName() const
{
  return _name;
}

Map::e_difficulty	Map::getDiff() const
{
  return _difficulty;
}

}
