#ifndef MAPLIST_H_
# define MAPLIST_H_

# include <unordered_map>
# include <string>
# include <list>
# include "Map.hpp"
# include "JSONDoc.hpp"

class JSONDoc;

namespace Bomberman
{

class		MapList
{
public:
  MapList();
  virtual ~MapList();
  Map*			getMap(std::string const& name) const;
  void			addMap(Map*);
  void			addMap(std::string const&, unsigned int, unsigned int);
  std::unordered_map<std::string, std::pair<unsigned int, unsigned int> > const&	getMapList() const;
  bool					operator==(MapList const& other) const;

private:
  std::unordered_map<std::string, std::pair<unsigned int, unsigned int> >	_maps;
  JSONDoc*									_json;
};

}

#endif /* !MAPLIST_H_ */
