#include <string>
#include "my_random.hpp"
#include "InvalidNbPlayers.hpp"
#include "InvalidDimensions.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"

namespace Bomberman
{

Map::Map()
{}

Map::Map(std::string name, unsigned int width, unsigned int height,
	 unsigned int nbJoueurs, e_difficulty difficulty,
	 RessourceStock* objects)
  : GenericMap<IObject*>(width, height), _name(name),
    _nbJoueurs(nbJoueurs), _difficulty(difficulty), _rcs(objects)
{
  this->_width = width;
  this->_height = height;
  if (this->_nbJoueurs == 0
      || this->_nbJoueurs > this->_width * this->_height / 12)
    throw new Exception::InvalidNbPlayers("Map Constructor");
  if (this->_height < 10 || this->_width < 10)
    throw new Exception::InvalidDimensions("Map Constructor");
  this->randomize();
  this->equalize();
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
      || this->_nbJoueurs > this->_width * this->_height / 12)
    throw new Exception::InvalidNbPlayers("Map Constructor");
  if (this->_height < 10 || this->_width < 10)
    throw new Exception::InvalidDimensions("Map Constructor");
}

void	Map::generateForm(unsigned int x, unsigned int y)
{
  IObject*	obj;

  if (my_random(1, 4) == 1)
    obj = this->_rcs->getObject(IObject::DESTROYABLEWALL);
  else
    obj = this->_rcs->getObject(IObject::WALL);
  this->setCellValue(x, y, obj);
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
	  if (my_random(2, 10) > this->_difficulty)
	    this->setCellValue(x, y, this->_rcs->getObject(IObject::EMPTY));
	  else
	    this->setCellValue(x, y, this->_rcs->getObject(IObject::DESTROYABLEWALL));
	  ++x;
	}
      ++y;
    }
  y = 2;
  while (y < this->_height - 2)
    {
      x = 2;
      while (x < this->_width - 2)
  	{
  	  if ((my_random(10, 100) + 5) / 10 > this->_difficulty)
  	    this->setCellValue(x, y, this->_rcs->getObject(IObject::DESTROYABLEWALL));
  	  else
  	    {
  	      this->setCellValue(x, y, this->_rcs->getObject(IObject::WALL));
	      this->generateForm(x + ((my_random(0, 1) == 1) ? (1) : (-1)), y);
	      this->generateForm(x, y + ((my_random(0, 1) == 1) ? (1) : (-1)));
  	      ++x;
  	    }
  	  x = x + 2;
  	}
      y = y + 2;
    }
}

bool	Map::addNoBlocking(unsigned int x, unsigned int y)
{
  unsigned int	posx;
  unsigned int	posy = 0;
  unsigned int	maxX = 0;
  unsigned int	maxY = 0;

  if (x > this->_width - 1 || y > this->_height - 1)
    return (false);
  maxX = ((x > this->_width - 2) || (x == 0));
  maxY = ((y > this->_height - 2) || (y == 0));
  x = x - (x != 0);
  y = y - (y != 0);
  while (posy < 3 - maxY)
    {
      posx = 0;
      while (posx < 3 - maxX)
	{
	  if (this->getCellValue(x + posx, y  + posy)->getObjectType() == IObject::WALL)
	    return (false);
	  ++posx;
	}
      ++posy;
    }
  this->setCellValue(x + 1, y + 1, this->_rcs->getObject(IObject::WALL));
  return (true);
}

bool	Map::checkDensity(unsigned int x, unsigned int y, unsigned int radius) const
{
  unsigned int	posx;
  unsigned int	posy = 0;

  while (posy < radius)
    {
      posx = 0;
      while (posx < radius)
	{
	  if (this->getCellValue(x + posx, y  + posy)->getObjectType() == IObject::WALL)
	    return (false);
	  ++posx;
	}
      ++posy;
    }
  return (true);
}

void	Map::equalize()
{
  unsigned int	x;
  unsigned int	y = 0;
  unsigned int	radius;
  bool		check;

  switch(this->_difficulty)
    {
    case EASY:
      radius = 4;
      break;
    case MEDIUM:
      radius = 3;
      break;
    case DIFFICULT:
      radius = 2;
      break;
    }
  while (y < this->_height)
    {
      x = 0;
      while (x < this->_width)
	{
	  if (((x + radius - 1) < this->_width) && ((y + radius - 1) < this->_height)
	      && this->checkDensity(x, y, radius))
	    {
	      if (!(check = this->addNoBlocking(x, y)))
		check = ((check == true) ? (true) : (this->addNoBlocking(x, y + radius - 1)));
	      if (!(check = ((check == true) ? (true) : (this->addNoBlocking(x + radius - 1,
									     y + radius - 1)))))
		check = ((check == true) ? (true) : (this->addNoBlocking(x + radius - 1, y)));
	      if (!check)
		check = this->addNoBlocking(x + radius / 2, y + radius / 2);
	    }
	  ++x;
	}
      ++y;
    }
}

float		Map::calcLong(unsigned int x1, unsigned int y1,
				      unsigned int x2, unsigned int y2)
{
  int		x = x1 - x2;
  int		y = y1 - y2;

  return (sqrt(pow(x, 2) + pow(y, 2)));
}

Map::TwoInt			Map::findEmptySpawn()
{
  Player*		player;
  float			tmp;
  float			rest;
  t_spawn		s = {0, 0, -1.0f, 0};
  bool			ok;

  for (unsigned int x = 0; x < getWidth(); x++)
    for (unsigned int y = 0; y < getHeight(); y++)
      {
	rest = -1.0f;
	ok = false;
	for (unsigned int i = 0; i < _rcs->getNbPlayer(); i++)
	  {
	    player = dynamic_cast<Player*>(_rcs->getPlayer(i));
	    if (player->isPlaced())
	      {
		tmp = calcLong(player->getX(), player->getY(), x, y);
		if (player->getX() == x && player->getY() == y)
		  ok = true;
		else if (tmp < rest || rest == -1)
		  rest = tmp;
	      }
	  }
	if ((rest > s.level || s.level == -1) && !ok)
	  {
	    s.posX = x;
	    s.posY = y;
	    s.level = rest;
	  }
      }
  addSpawn(s.posX, s.posY);
  return std::make_pair(s.posX, s.posY);
}

void			Map::pushSpawn(unsigned int x, unsigned int y, unsigned int level)
{
  t_spawn	spawn = { x, y, float(level), 0};

  this->_spawnList.push_back(spawn);
}

void	Map::addSpawn(unsigned int x, unsigned int y)
{
  this->setCellValue(x, y, this->_rcs->getObject(IObject::EMPTY));
  this->setCellValue(x + (((x > 0 && my_random(0, 1)) || x == _width - 1) ? (-1) : (1)), y,
  		     this->_rcs->getObject(IObject::EMPTY));
  this->setCellValue(x, y + (((y > 0 && my_random(0, 1)) || y == _height - 1) ? (-1) : (1)),
  		     this->_rcs->getObject(IObject::EMPTY));
}

void	Map::menger(unsigned int sizeX, unsigned int sizeY, unsigned int level,
		    unsigned int saveX, unsigned int saveY, bool first)
{
  unsigned int	written = 0;
  unsigned int	x = 0;
  unsigned int	y;

  if (!level || !sizeX || !sizeY)
    return ;
  std::cout << level << std::endl;
  if (first)
    pushSpawn(sizeX / 2 - !(sizeX % 2), sizeY / 2 - !(sizeY % 2), level);
  else
    pushSpawn(saveX + sizeX / 3, saveY + sizeY / 3, level);
  while (x < (sizeX - 1))
    {
      y = 0;
      while (y < (sizeY - 1))
	{
	  if (written != 4)
	    menger(sizeX / 3, sizeY / 3, level - 1, saveX + x, saveY + y, false);
	  ++written;
	  y += sizeY / 3;
	}
      x += sizeX / 3;
    }
}

unsigned int	Map::findLevel()
{
  unsigned int	level = 1;
  unsigned int	res = 9;
  unsigned int	save = 8;

  if (this->_nbJoueurs <= 1)
    return (0);
  while (res < this->_nbJoueurs)
    {
      save = save * 8;
      res += save;
      ++level;
    }
  return (level + 1);
}

void	Map::spawnize()
{
  //menger(this->_width, this->_height, this->findLevel(), 0, 0, true);
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

bool		Map::isIn(unsigned int x, unsigned int y) const
{
  return (x < getHeight() && y < getWidth());
}

void		Map::killPlayers(unsigned int x, unsigned int y, Player *player) const
{
  for (unsigned int i = 0; i < _rcs->getNbPlayer(); i++)
    {
      if (dynamic_cast<Player*>(_rcs->getPlayer(i))->getX() == x &&
	  dynamic_cast<Player*>(_rcs->getPlayer(i))->getY() == y)
	{
	  if (dynamic_cast<Player*>(_rcs->getPlayer(i))->tryToKill() &&
	      dynamic_cast<Player*>(_rcs->getPlayer(i)) != player)
	    player->incScore();
	}
    }
}

void		Map::checkBombsOnMap()
{
  for (std::list<BombTimer*>::iterator it = _bombs.begin(); it != _bombs.end(); it++)
    {
      if ((*it)->finish((*it)->getX(), (*it)->getY(), this))
  	{
	  if (getCellValue((*it)->getX(), (*it)->getY()) == (*it))
	    killObject((*it)->getX(), (*it)->getY());
  	  delete *it;
  	  it = _bombs.erase(it);
  	}
    }
  for (std::list<Fire*>::iterator it = _firebox.begin(); it != _firebox.end(); it++)
    {
      if ((*it)->isFinished())
  	{
	  if (getCellValue((*it)->getX(), (*it)->getY()) == (*it))
	    killObject((*it)->getX(), (*it)->getY());
	  if ((*it)->getBuff() != NULL)
	    setCellValue((*it)->getX(), (*it)->getY(), (*it)->getBuff());
  	  delete (*it);
  	  it = _firebox.erase(it);
  	}
    }
  for (unsigned int i = 0; i < _rcs->getNbPlayer(); i++)
    {
      dynamic_cast<Player*>(_rcs->getPlayer(i))->checkBuffList();
    }
}

void		Map::addBomb(BombTimer *bomb)
{
  _bombs.push_back(bomb);
}

void		Map::addFire(Player *player, unsigned int x, unsigned int y)
{
  if (getCellValue(x, y)->getObjectType() != IObject::FIRE)
    {
      Fire		*fire = new Fire(player, x, y);

      if (getCellValue(x, y)->getObjectType() == IObject::BONUS)
	fire->setBuff(getCellValue(x, y));
      setCellValue(x, y, fire);
      _firebox.push_back(fire);
    }
}

void		Map::addFire(Player *player, unsigned int x, unsigned int y, float time)
{
  if (getCellValue(x, y)->getObjectType() != IObject::FIRE)
    {
      Fire		*fire = new Fire(player, x, y, time);

      if (getCellValue(x, y)->getObjectType() == IObject::BONUS)
	fire->setBuff(getCellValue(x, y));
      setCellValue(x, y, fire);
      _firebox.push_back(fire);
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
