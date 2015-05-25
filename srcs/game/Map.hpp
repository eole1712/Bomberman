#ifndef MAP_H_
# define MAP_H_

# include <string>
# include <vector>
# include "IObject.hpp"
# include "GenericMap.hpp"

namespace Bomberman
{

class Map
  : public GenericMap<IObject *>
{
public:
  Map(std::vector<std::string>, unsigned int width, unsigned int height);
  virtual ~Map();

public:
  void			initMapToEmpty();

public:
  IObject*		getObject(unsigned int x, unsigned int y) const;
  void			setObject(unsigned int x, unsigned int y, IObject *obj);
  void			moveObject(unsigned int xs, unsigned int ys, unsigned int xd, unsigned int yd);
  void			killObject(unsigned int x, unsigned int y);

private:
  unsigned int		_nbPlayers;
  std::vector<IObject*>	_players;
  std::vector<IObject*>	_buffs;
  IObject		*_empty;
};

}

#endif /* !MAP_H_ */
