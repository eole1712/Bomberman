#ifndef RESSOURCESTOCK_H_
# define RESSOURCESTOCK_H_

# include <vector>
# include <string>
# include "IObject.hpp"
# include "IBuff.hpp"
# include "Player.hpp"

namespace Bomberman
{

class RessourceStock
{
public:
  RessourceStock(std::vector<std::string> const &);
  virtual ~RessourceStock();

private:
  RessourceStock(const RessourceStock &);
  RessourceStock &operator=(const RessourceStock &);

public:
  IObject	*getObject(IObject::Type) const;
  IObject	*getBuff(IBuff::Type) const;
  IObject	*getPlayer(std::string const &) const;
  IObject	*getPlayer(unsigned int) const;

private:
  std::vector<IObject *>	_players;
  std::vector<IObject *>	_buffs;
  std::vector<IObject *>	_bombs;
  std::vector<IObject *>	_objects;
};

}

#endif /* !RESSOURCESTOCK_H_ */
