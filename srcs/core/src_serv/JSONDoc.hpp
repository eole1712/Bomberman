#ifndef JSONDOC_H_
# define JSONDOC_H_

#include <string>
#include "rapidjson.h"
#include "document.h"
#include "Score.hpp"
#include "Player.hpp"

class JSONDoc
{
public:
  JSONDoc();
  JSONDoc(const std::string&);
  ~JSONDoc();
  bool parse(const std::string&);
  //const std::string& operator[](std::string const&);
  template <typename T>
  void serialize(T const& obj)
  {
    ;
  }
  template <typename T>
  T unserialize() const
  {
    ;
  }
  void writeDown(std::string const& filename);

private:
  rapidjson::Document _doc;
  std::string _filename;
};

template<>
void JSONDoc::serialize<Bomberman::Score>(const Bomberman::Score &obj);

template<>
Bomberman::Score JSONDoc::unserialize<Bomberman::Score>() const;

template<>
void JSONDoc::serialize<Bomberman::Player>(const Bomberman::Player &obj);

template<>
Bomberman::Player JSONDoc::unserialize<Bomberman::Player>() const;



#endif /* !JSONDOC_H_ */
