#ifndef RESSOURCESTOCK_H_
# define RESSOURCESTOCK_H_

# include <vector>
# include <string>
# include "IObject.hpp"
# include "IBuff.hpp"
# include "IBomb.hpp"
# include "Player.hpp"
# include "ScoreList.hpp"
# include "Sound.hpp"
# include "RessourceStock.hpp"

namespace Bomberman
{

class RessourceStock
{
public:
  enum SoundType { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE,
		   FIRSTBLOOD, MINE, PREPARE, SUICIDE };

  static unsigned int const	nbSounds;

  RessourceStock();
  RessourceStock(std::vector<std::string> const &, ScoreList*);
  RessourceStock(std::vector<Bomberman::Player*> const& players);
  virtual ~RessourceStock();
  RessourceStock(const RessourceStock &);
  RessourceStock &operator=(const RessourceStock &);

public:
  IObject	*getObject(IObject::Type) const;
  IObject	*getBuff(IBuff::Type) const;
  IObject	*getBomb(Bomb::Type) const;
  SoundManager	*getSound(SoundType);
  IObject	*getPlayer(std::string const &) const;
  IObject	*getPlayer(unsigned int) const;
  unsigned int	getNbPlayer() const;

private:
  std::vector<IObject *>	_players;
  std::vector<IObject *>	_buffs;
  std::vector<IObject *>	_bombs;
  std::vector<IObject *>	_objects;
  std::vector<std::string>	_sounds;
};

}

#endif /* !RESSOURCESTOCK_H_ */
