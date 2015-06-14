#ifndef MAP_H_
# define MAP_H_

# include <map>
# include "GenericMap.hpp"
# include "IObject.hpp"
# include "RessourceStock.hpp"
# include "BombTimer.hpp"
# include "Fire.hpp"

namespace Bomberman
{
class RessourceStock;
class Map : public GenericMap<IObject*>
{
public:
  typedef std::pair<unsigned int, unsigned int> PosPair;
  typedef std::map<std::pair<unsigned int, unsigned int>, BombTimer*> MapBomb;
  typedef std::pair<unsigned int, unsigned int> TwoInt;

private:

  void			init(unsigned int, unsigned int);
  void			generateForm(unsigned int, unsigned int);
  void			randomize();
  bool			addNoBlocking(unsigned int, unsigned int);
  bool			checkDensity(unsigned int, unsigned int, unsigned int) const;
  void			equalize();
  void			pushSpawn(unsigned int, unsigned int, unsigned int);
  TwoInt		addSpawn(unsigned int, unsigned int);

public:
  enum e_difficulty	{ EASY = 7, MEDIUM, DIFFICULT };

  struct		t_spawn
  {
    unsigned int	posX;
    unsigned int	posY;
    float		level;
    unsigned int	stock;
  };

  Map();
  Map(std::string const&, unsigned int, unsigned int, unsigned int, e_difficulty, RessourceStock *, bool god = false);
  Map(std::string const&, unsigned int, unsigned int, unsigned int, e_difficulty, bool god = false);
  virtual ~Map() {};

public:
  RessourceStock	*getRcs() const;
  void			setRcs(RessourceStock*);
  TwoInt		findEmptySpawn();
  float			calcLong(unsigned int x1, unsigned int y1,
				 unsigned int x2, unsigned int y2);

public:
  void			swapObjects(unsigned int x, unsigned int y, unsigned int nx, unsigned int ny);
  void			killObject(unsigned int x, unsigned int y);

public:
  std::string const&	getName() const;
  unsigned int		getNumberPlayers() const;
  e_difficulty		getDiff() const;
  bool			hasToQuit() const;

public:
  bool			isIn(unsigned int x, unsigned int y) const;
  void			killPlayers(unsigned int x, unsigned int y, Player *);
  void			checkBombsOnMap();
  void			addBomb(BombTimer*);
  void			addFire(Fire*);
  void			addFire(Player*, unsigned int, unsigned int);
  void			addFire(Player*, unsigned int, unsigned int, float);

public:
  void			pauseBombs();
  void			continueBombs();

public:
  bool			isGod() const;

private:
  std::string		_name;
  unsigned int		_order;
  unsigned int		_nbJoueurs;
  e_difficulty		_difficulty;
  RessourceStock*	_rcs;
  std::list<t_spawn>	_spawnList;
  std::list<BombTimer*>	_bombs;
  std::list<Fire*>	_firebox;
  bool			_quit;
  bool			_god;
};

}
#endif /* !MAP_H_ */
