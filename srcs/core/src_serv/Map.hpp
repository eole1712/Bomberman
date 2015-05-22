#ifndef MAP_H_
# define MAP_H_

#include <unordered_map>

namespace Bomberman
{

class IObject;

class Map
{
public:
  Map();
  virtual ~Map();

private:
  std::unordered_map<std::pair<unsigned int, unsigned int>, IObject*> _map;
  std::string _name;
  std::pair<unsigned int, unsigned int> _dimensions;

};

}
#endif /* !MAP_H_ */
