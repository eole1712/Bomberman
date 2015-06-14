#include "IBuff.hpp"
#include "BombVirus.hpp"
#include "my_random.hpp"

namespace Bomberman
{

namespace Bomb
{

Virus::Virus()
{}

Virus::~Virus()
{}

int		Virus::getDuration() const
{
  return 4;
}

Bomb::Type	Virus::getBombType() const
{
  return Bomb::VIRUS;
}

IObject::Type	Virus::getObjectType() const
{
  return IObject::VIRUS;
}

bool		Virus::isNull() const
{
  return false;
}

void		Virus::explose(int x, int y, Map *map, unsigned int, Player *player) const
{
  map->killObject(x, y);
  for (int i = x; i >= 0 ; --i)
    {
      if (i == 0 ||
	  map->getCellValue(i - 1, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i - 1, y)->getObjectType() == IObject::WALL)
	{
	  player->putTimedBomb(i, y);
	  break;
	}
    }
  for (unsigned int i = x; i < map->getWidth() ; ++i)
    {
      if (i == (map->getWidth() - 1) ||
	  map->getCellValue(i + 1, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i + 1, y)->getObjectType() == IObject::WALL)
	{
	  player->putTimedBomb(i, y);
	  break;
	}
    }
  for (int i = y; i >= 0 ; --i)
    {
      if (i == 0 ||
	  map->getCellValue(x, i - 1)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i - 1)->getObjectType() == IObject::WALL)
	{
	  player->putTimedBomb(x, i);
	  break;
	}
    }
  for (unsigned int i = y; i < map->getHeight() ; ++i)
    {
      if (i == (map->getHeight() - 1) ||
	  map->getCellValue(x, i + 1)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i + 1)->getObjectType() == IObject::WALL)
	{
	  player->putTimedBomb(x, i);
	  break;
	}
    }
}

  void		Virus::setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					  int y, unsigned int range) const
  {
    IBomb*	classic = dynamic_cast<IBomb*>(realMap->getRcs()->getBomb(CLASSIC));

    for (int i = x; i >= 0 ; --i)
      {
	if (i == 0 ||
	    realMap->getCellValue(i - 1, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	    realMap->getCellValue(i - 1, y)->getObjectType() == IObject::WALL ||
	    realMap->getCellValue(i, y)->getObjectType() == IObject::PLAYER)
	  {
	    classic->setBlastRangeToMap(map, realMap, i, y, range);
	    break;
	  }
      }
    for (unsigned int i = x; i < realMap->getWidth() ; ++i)
      {
	if (i == (realMap->getWidth() - 1) ||
	    realMap->getCellValue(i + 1, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	    realMap->getCellValue(i + 1, y)->getObjectType() == IObject::WALL ||
	    realMap->getCellValue(i, y)->getObjectType() == IObject::PLAYER)
	  {
	    classic->setBlastRangeToMap(map, realMap, i, y, range);
	    break;
	  }
      }
    for (int i = y; i >= 0 ; --i)
      {
	if (i == 0 ||
	    realMap->getCellValue(x, i - 1)->getObjectType() == IObject::DESTROYABLEWALL ||
	    realMap->getCellValue(x, i - 1)->getObjectType() == IObject::WALL ||
	    realMap->getCellValue(x, i)->getObjectType() == IObject::PLAYER)
	  {
	    classic->setBlastRangeToMap(map, realMap, x, i, range);
	    break;
	  }
      }
    for (unsigned int i = y; i < realMap->getHeight() ; ++i)
      {
	if (i == (realMap->getHeight() - 1) ||
	    realMap->getCellValue(x, i + 1)->getObjectType() == IObject::DESTROYABLEWALL ||
	    realMap->getCellValue(x, i + 1)->getObjectType() == IObject::WALL ||
	    realMap->getCellValue(x, i)->getObjectType() == IObject::PLAYER)
	  {
	    classic->setBlastRangeToMap(map, realMap, x, i, range);
	    break;
	  }
      }
  }

IBomb*		Virus::clone() const
{
  return new Virus;
}

std::string	Virus::getClassName() const
{
  return "Virus";
}

}

}
