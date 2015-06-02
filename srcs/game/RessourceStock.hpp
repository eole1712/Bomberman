#ifndef RESSOURCESTOCK_H_
# define RESSOURCESTOCK_H_

# include <vector>
# include <string>
# include "IObject.hpp"
# include "IBuff.hpp"
# include "IBomb.hpp"
# include "Player.hpp"

namespace Bomberman
{

class RessourceStock
{
public:
  RessourceStock(std::vector<std::string> const &);
  RessourceStock(std::vector<Bomberman::Player*> const& players);
  virtual ~RessourceStock();

private:
  RessourceStock(const RessourceStock &);
  RessourceStock &operator=(const RessourceStock &);

public:
  IObject	*getObject(IObject::Type) const;
  IObject	*getBuff(IBuff::Type) const;
  IObject	*getBomb(IBomb::Type) const;
  IObject	*getPlayer(std::string const &) const;
  IObject	*getPlayer(unsigned int) const;
  unsigned int	getNbPlayer() const;

private:
  std::vector<IObject *>	_players;
  std::vector<IObject *>	_buffs;
  std::vector<IObject *>	_bombs;
  std::vector<IObject *>	_objects;
};

}

#endif /* !RESSOURCESTOCK_H_ */
