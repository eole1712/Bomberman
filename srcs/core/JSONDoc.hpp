#ifndef JSONDOC_H_
# define JSONDOC_H_

#include <string>
#include "rapidjson.h"
#include "document.h"
#include "ScoreList.hpp"
#include "Player.hpp"
#include "MapList.hpp"

namespace Bomberman
{
class MapList;
}

class JSONDoc
{
public:
  JSONDoc();
  JSONDoc(const std::string&);
  ~JSONDoc();
  bool		parse(const std::string&);
  template <typename T>
  void		serialize(T const& obj)
  {
    ;
  }
  template <typename T>
  T		unserialize(std::string const& name="") const
  {
    (void)name;
    throw (std::runtime_error("Non specified use of template"));
  }
  void		writeDown(std::string const& filename);

private:
  rapidjson::Document	_doc;
  std::string		_filename;
};

template<>
void			JSONDoc::serialize<Bomberman::ScoreList>(const Bomberman::ScoreList& obj);

template<>
Bomberman::ScoreList*	JSONDoc::unserialize<Bomberman::ScoreList*>(std::string const& name) const;

template<>
void			JSONDoc::serialize<Bomberman::MapList>(const Bomberman::MapList& obj);

template<>
Bomberman::MapList*	JSONDoc:unserialize<Bomberman::MapList*>(std::string const& name);

template<>
void			JSONDoc::serialize<Bomberman::Player>(const Bomberman::Player& obj);

template<>
Bomberman::Player*	JSONDoc::unserialize<Bomberman::Player*>(std::string const& name) const;

template<>
void			JSONDoc::serialize<Bomberman::Map>(const Bomberman::Map& obj);

template<>
Bomberman::Map*		JSONDoc::unserialize<Bomberman::Map*>(std::string const& name) const;

#endif /* !JSONDOC_H_ */
