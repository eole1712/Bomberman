#ifndef MAP_H_
# define MAP_H_

#include <unordered_map>

namespace Bomberman
{

class IObject;

class Map
{
public:
  Map(std::string, std::pair<unsigned int, unsigned int>);
  Map(std::string, unsigned int, unsigned int);
  virtual ~Map();

  std::string	getName() const;
  std::pair<unsigned int, unsigned int>	getDimensions() const;
  IObject*	getCell(std::pair<unsigned int, unsigned int>) const;
  IObject*	getCell(unsigned int, unsigned int) const;

  void	setName(std::string);
  void	setCell(std::pair<unsigned int, unsigned int>, IObject*);
  void	setCell(unsigned int, unsigned int, IObject*);

private:
  std::string	_name;
  std::pair<unsigned int, unsigned int> const	_dimensions;
  std::unordered_map<std::pair<unsigned int, unsigned int>, IObject*>	_map;
};

}
#endif /* !MAP_H_ */
