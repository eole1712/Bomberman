#ifndef MAP_H_
# define MAP_H_

# include <map>
# include "GenericMap.hpp"
# include "IObject.hpp"
# include "RessourceStock.hpp"
# include "BombTimer.hpp"

namespace Bomberman
{

class Map : public GenericMap<IObject*>
{
public:
  typedef std::pair<unsigned int, unsigned int> PosPair;
  typedef std::map<std::pair<unsigned int, unsigned int>, BombTimer*> MapBomb;

private:

  void	generateForm(unsigned int, unsigned int);
  void	randomize();
  bool	addNoBlocking(unsigned int, unsigned int);
  bool	checkDensity(unsigned int, unsigned int, unsigned int);
  void	equalize();
  void	spawnize();

public:
  enum e_difficulty	{ EASY = 7, MEDIUM, DIFFICULT };

  Map(std::string, unsigned int, unsigned int, unsigned int, e_difficulty, RessourceStock *);
  Map(std::string, unsigned int, unsigned int, unsigned int, e_difficulty);
  virtual ~Map() {};

  RessourceStock	*getRcs() const;

public:
  void			swapObjects(unsigned int x, unsigned int y, unsigned int nx, unsigned int ny);
  void			killObject(unsigned int x, unsigned int y);

public:
  std::string const&	getName() const;
  unsigned int		getNumberPlayers() const;
  e_difficulty		getDiff() const;

public:
  bool		isIn(unsigned int x, unsigned int y);
  void		checkBomb(unsigned int x, unsigned int y);
  void		killPlayers(unsigned int x, unsigned int y);
  void		checkBombsOnMap();
  void		addBomb(BombTimer*);


private:
  std::string		_name;
  unsigned int		_nbJoueurs;
  e_difficulty		_difficulty;
  RessourceStock*	_rcs;
  std::list<BombTimer*>	_bombs;
};

}
#endif /* !MAP_H_ */
