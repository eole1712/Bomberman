#include "Map.hpp"
#include "StringConversion.hpp"

namespace Bomberman
{
  namespace AI
  {
    /*
    ** Static member variables
    */
    const StateMap::putCellBook		StateMap::putCellHandleBook	= StateMap::getPutCellBook();

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
      _playersCoo = other._playersCoo;
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
	      putCellBook::const_iterator	it = putCellHandleBook.find(map.getCellValue(x, y)->getObjectType());

	      if (it == putCellHandleBook.end())
		{
		  if (getCellValue(x, y) == AI::UNKNOWN)
		    setCellValue(x, y, AI::SAFE);
		}
	      else
		(this->*(it->second))(map, x, y);

	    }
	}
      _playersCoo.clear();
      for (unsigned int i = 0; i < map.getRcs()->getNbPlayer(); ++i)
      	{
      	  Player*	player = map.getRcs()->getPlayer(i);

      	  if (player->isAlive())
      	    _playersCoo.push_back(std::tuple<std::string, int, int>(player->getName(), player->getX(), player->getY()));
      	}
    }

    int		StateMap::getPlayerPosX(unsigned int player) const
    {
      if (player >= _playersCoo.size())
	return (-1);
      return (std::get<1>(_playersCoo[player]));
    }

    int		StateMap::getPlayerPosY(unsigned int player) const
    {
      if (player >= _playersCoo.size())
	return (-1);
      return (std::get<2>(_playersCoo[player]));
    }

    std::string const&	StateMap::getPlayerName(unsigned int player) const
    {
      return (std::get<0>(_playersCoo[player]));
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

    void	StateMap::putBlock(Bomberman::Map const& map, unsigned int x, unsigned int y)
    {
      static_cast<void>(map);
      setCellValue(x, y, AI::BLOCK);
    }

    void	StateMap::putDestroyable(Bomberman::Map const& map, unsigned int x, unsigned int y)
    {
      static_cast<void>(map);
      setCellValue(x, y, AI::DESTROYABLE);
    }

    void	StateMap::putBonus(Bomberman::Map const& map, unsigned int x, unsigned int y)
    {
      static_cast<void>(map);
      if (getCellValue(x, y) == AI::UNKNOWN || getCellValue(x, y) == AI::SAFE)
	setCellValue(x, y, AI::BONUS);
    }

    void	StateMap::putBomb(Bomberman::Map const& map, unsigned int x, unsigned int y)
    {
      BombTimer*	bomb = dynamic_cast<BombTimer*>(map.getCellValue(x, y));

      bomb->setBlastRangeToMap(this, &map);
      setCellValue(x, y, AI::BLOCK);
    }

    /*
    ** Static member functions
    */
    StateMap::putCellBook	StateMap::getPutCellBook()
    {
      putCellBook		book;

      book[IObject::FIRE] = &StateMap::putBlock;
      book[IObject::WALL] = &StateMap::putBlock;
      book[IObject::DESTROYABLEWALL] = &StateMap::putDestroyable;
      book[IObject::BONUS] = &StateMap::putBonus;
      book[IObject::BOMB] = &StateMap::putBomb;
      book[IObject::MINE] = &StateMap::putBomb;
      book[IObject::BARREL] = &StateMap::putBomb;
      book[IObject::VIRUS] = &StateMap::putBomb;
      return book;
    }
  }
}
