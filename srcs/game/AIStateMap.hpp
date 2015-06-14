#ifndef __AISTATEMAP_HPP__
# define __AISTATEMAP_HPP__

# include <vector>
# include <utility>
# include <tuple>
# include "GenericMap.hpp"
# include "Map.hpp"

namespace Bomberman
{
  class Map;

  namespace AI
  {
    enum Cell
      {
	BLOCK = 0,	/* wall + bombs + fire */
	DESTROYABLE,
	SAFE,
	UNSAFE,
	PLAYER,
	BONUS,
	UNKNOWN		/* if the cell hasn't been initialized */
      };

    class StateMap : public GenericMap<AI::Cell>
    {
    public:
      StateMap();
      virtual ~StateMap();

    public:
      StateMap(StateMap const& other);
      StateMap&		operator=(StateMap const& other);

    public:
      StateMap(Bomberman::Map const& map);

    public:
      std::string	toString() const;

    public:
      int			getPlayerPosX(unsigned int player) const;
      int			getPlayerPosY(unsigned int player) const;
      std::string const&	getPlayerName(unsigned int player) const;
      int			getNbPlayers() const;
      int			getIntCell(unsigned int x, unsigned int y) const;

    public:
      void			setAICells(Bomberman::Map const& map);
      int			getIntWidth() const;
      int			getIntHeight() const;

    protected:
      void			clear();

    protected:
      std::vector<std::tuple<std::string, int, int> >	_playersCoo;
    };
  }
}

#endif /* !__AISTATEMAP_HPP__ */
