#include "Map.hpp"

namespace Bomberman
{
  namespace AI
  {
    /*
    ** Constructors/Destructor
    */
    StateMap::StateMap() : GenericMap<Cell>()
    {
    }

    StateMap::StateMap(Map const& map) : GenericMap<Cell>(map.getWidth(), map.getHeight())
    {
      setAICells(map);
    }

    StateMap::~StateMap()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    StateMap::StateMap(StateMap const& other) : GenericMap<Cell>(other)
    {
    }

    StateMap&	StateMap::operator=(StateMap const& other)
    {
      GenericMap<Cell>::operator=(other);
      return (*this);
    }

    /*
    ** Public member functions
    */
    void		StateMap::setAICells(Bomberman::Map const& map)
    {
      if (map.getWidth() != _width || map.getHeight() != _height)
	throw std::runtime_error("AI's Map and map aren't the same dimensions.");
      for (unsigned int y = 0; y < _height; y++)
	{
	  for (unsigned int x = 0; x < _width; x++)
	    {
	      switch (map.getCellValue(x, y)->getObjectType())
		{
		case (IObject::PLAYER):
		  setCellValue(x, y, AI::PLAYER);
		  break ;
		case (IObject::FIRE):
		case (IObject::WALL):
		  setCellValue(x, y, AI::BLOCK);
		break ;
		case (IObject::DESTROYABLEWALL):
		  setCellValue(x, y, AI::DESTROYABLE);
		  break ;
		case (IObject::BOMB):
		  {
		    BombTimer*	bomb = dynamic_cast<BombTimer*>(map.getCellValue(x, y));

		    bomb->setBlastRangeToMap(this, &map);
		    break ;
		  }
		default:
		  setCellValue(x, y, AI::SAFE);
		  break ;
		}
	    }
	}
    }
  }
}
