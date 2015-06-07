#ifndef __AIMAP_HPP__
# define __AIMAP_HPP__

# include "GenericMap.hpp"
# include "Map.hpp"

namespace Bomberman
{
  class Map;

  namespace AI
  {
    enum Cell
      {
	BLOCK,		/* wall + bombs + fire */
	DESTROYABLE,
	SAFE,
	UNSAFE,
	PLAYER
      };

    class StateMap : public GenericMap<AI::Cell>
    {
    public:
      StateMap();
      virtual ~StateMap();

    public:
      StateMap(StateMap const& other);
      StateMap&	operator=(StateMap const& other);

    public:
      StateMap(Bomberman::Map const& map);

    public:
      void	setAICells(Bomberman::Map const& map);
    };
  }
}

#endif /* !__AIMAP_HPP__ */
