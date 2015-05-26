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
  enum e_difficulty	{ EASY = 1, MEDIUM, DIFFICULT };

  Map(std::string, unsigned int, unsigned int, unsigned int, e_difficulty, RessourceStock const&);
  virtual ~Map() {};

  void	randomize(RessourceStock const&);

private:
  std::string	_name;
  unsigned int	_nbJoueurs;
  e_difficulty	_difficulty;
};

}
#endif /* !MAP_H_ */
