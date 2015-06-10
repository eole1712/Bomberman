#include "Map.hpp"
#include "StringConversion.hpp"

namespace Bomberman
{
  namespace AI
  {
    /*
    ** Constructors/Destructor
    */
    StateMap::StateMap() : GenericMap<Cell>()
    {
      clear();
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
    std::string		StateMap::toString() const
    {
      std::string	map;

      for (unsigned int y = 0; y < _height; y++)
	{
	  for (unsigned int x = 0; x < _width; x++)
	    {
	      map += Conversion::typeToString<int>(getCellValue(x, y));
	      if (x == _width - 1)
		map += " ";
	    }
	  map += "\n";
	}
      return (map);
    }

    void		StateMap::setAICells(Bomberman::Map const& map)
    {
      if (map.getWidth() != _width || map.getHeight() != _height)
	throw std::runtime_error("AI's Map and map aren't the same dimensions.");
      clear();
      for (unsigned int y = 0; y < _height; y++)
	{
	  for (unsigned int x = 0; x < _width; x++)
	    {
	      switch (map.getCellValue(x, y)->getObjectType())
		{
		case (IObject::FIRE):
		case (IObject::WALL):
		  setCellValue(x, y, AI::BLOCK);
		break ;
		case (IObject::DESTROYABLEWALL):
		  setCellValue(x, y, AI::DESTROYABLE);
		  break ;
		case (IObject::BONUS):
		  if (getCellValue(x, y) == AI::UNKNOWN || getCellValue(x, y) == AI::SAFE)
		    setCellValue(x, y, AI::BONUS);
		  break ;
		case (IObject::BOMB):
		case (IObject::MINE):
		case (IObject::BARREL):
		  {
		    BombTimer*	bomb = dynamic_cast<BombTimer*>(map.getCellValue(x, y));

		    bomb->setBlastRangeToMap(this, &map);
		    setCellValue(x, y, AI::BLOCK);
		    break ;
		  }
		default:
		  if (getCellValue(x, y) == AI::UNKNOWN)
		    setCellValue(x, y, AI::SAFE);
		  break ;
		}
	    }
	}
      _playersCoo.clear();
      for (unsigned int i = 0; i < map.getRcs()->getNbPlayer(); ++i)
      	{
      	  Player*	player = dynamic_cast<Player*>(map.getRcs()->getPlayer(i));

      	  if (player->isAlive())
      	    _playersCoo.push_back(std::pair<int, int>(player->getX(), player->getY()));
      	}
    }

    int		StateMap::getPlayerPosX(unsigned int player) const
    {
      if (player >= _playersCoo.size())
	return (-1);
      return (_playersCoo[player].first);
    }

    int		StateMap::getPlayerPosY(unsigned int player) const
    {
      if (player >= _playersCoo.size())
	return (-1);
      return (_playersCoo[player].second);
    }

    int		StateMap::getNbPlayers() const
    {
      return (_playersCoo.size());
    }

    int		StateMap::getIntCell(unsigned int x, unsigned int y) const
    {
      return (getCellValue(x, y));
    }

    int		StateMap::getIntWidth() const
    {
      return (_width);
    }

    int		StateMap::getIntHeight() const
    {
      return (_height);
    }

    /*
    ** Protected member functions
    */
    void	StateMap::clear()
    {
      for (unsigned int y = 0; y < _height; y++)
	{
	  for (unsigned int x = 0; x < _width; x++)
	    {
	      setCellValue(x, y, AI::UNKNOWN);
	    }
	}
    }
  }
}
