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
  return IObject::BOMB;
}

bool		Virus::isNull() const
{
  return false;
}

void		Virus::explose(int x, int y, Map *map, unsigned int, Player *player) const
{
  for (int i = x; i >= 0 ; --i)
    {
      if (i == 0 ||
	  map->getCellValue(i - 1, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i - 1, y)->getObjectType() == IObject::WALL ||
	  map->getCellValue(i, y)->getObjectType() == IObject::PLAYER)
	{
	  player->putTimedBomb(i, y);
	  break;
	}
    }
  for (unsigned int i = x; i < map->getWidth() ; ++i)
    {
      if (i == (map->getWidth() - 1) ||
	  map->getCellValue(i + 1, y)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(i + 1, y)->getObjectType() == IObject::WALL ||
	  map->getCellValue(i, y)->getObjectType() == IObject::PLAYER)
	{
	  player->putTimedBomb(i, y);
	  break;
	}
    }
  for (int i = y; i >= 0 ; --i)
    {
      if (i == 0 ||
	  map->getCellValue(x, i - 1)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i - 1)->getObjectType() == IObject::WALL ||
	  map->getCellValue(x, i)->getObjectType() == IObject::PLAYER)
	{
	  player->putTimedBomb(x, i);
	  break;
	}
    }
  for (unsigned int i = y; i < map->getHeight() ; ++i)
    {
      if (i == (map->getHeight() - 1) ||
	  map->getCellValue(x, i + 1)->getObjectType() == IObject::DESTROYABLEWALL ||
	  map->getCellValue(x, i + 1)->getObjectType() == IObject::WALL ||
	  map->getCellValue(x, i)->getObjectType() == IObject::PLAYER)
	{
	  player->putTimedBomb(x, i);
	  break;
	}
    }
}

  void		Virus::setBlastRangeToMap(AI::StateMap* map, Map const* realMap, int x,
					  int y, unsigned int range) const
  {
    static_cast<void>(map);
    static_cast<void>(realMap);
    static_cast<void>(x);
    static_cast<void>(y);
    static_cast<void>(range);
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