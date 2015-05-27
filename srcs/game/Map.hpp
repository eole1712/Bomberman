#ifndef MAP_H_
# define MAP_H_

# include "GenericMap.hpp"
# include "IObject.hpp"
# include "RessourceStock.hpp"

namespace Bomberman
{

class Map : public GenericMap<IObject*>
{
public:
  enum e_difficulty	{ EASY = 5, MEDIUM, DIFFICULT };

  Map(std::string, unsigned int, unsigned int, unsigned int, e_difficulty, RessourceStock *);
  virtual ~Map() {};

  void	randomize(RessourceStock const&);
  RessourceStock	*getRcs() const;

public:
  void		swapObjects(unsigned int x, unsigned int y, unsigned int nx, unsigned int ny);
  void		killObject(unsigned int x, unsigned int y);

public:
  bool		isIn(unsigned int x, unsigned int y);
  void		checkBomb(unsigned int x, unsigned int y);
  void		killPlayers(unsigned int x, unsigned int y);
  void		checkBombsOnMap();

private:
  std::string	_name;
  unsigned int	_nbJoueurs;
  e_difficulty	_difficulty;
  RessourceStock *_rcs;
};

}
#endif /* !MAP_H_ */
