#include <fstream>
#include <iostream>
#include <algorithm>
#include "stringbuffer.h"
#include "writer.h"
#include "document.h"
#include "prettywriter.h"
#include "JSONDoc.hpp"

JSONDoc::JSONDoc()
{
  ;
}

JSONDoc::JSONDoc(std::string const& name)
{
  std::ifstream is;
  std::string str;

  is.open(name);
  if (is.good())
    {
      is >> str;
      rapidjson::StringStream rs(str.c_str());
      _doc.ParseStream<rapidjson::kParseDefaultFlags, rapidjson::StringStream>(rs);
      _filename = name;
    }
}

JSONDoc::~JSONDoc()
{
  writeDown(_filename);
}

bool	JSONDoc::parse(const std::string &name)
{
  std::ifstream is;
  std::string str;

  is.open(name);
  if (is.good())
    {
      is >> str;
      rapidjson::StringStream rs(str.c_str());
      _doc.ParseStream<rapidjson::kParseDefaultFlags, rapidjson::StringStream>(rs);
      _filename = name;
      return true;
    }
  return false;
}

void	JSONDoc::writeDown(const std::string &filename)
{
  std::ofstream os(filename);

  if (os.good())
    {
      rapidjson::StringBuffer sb;
      rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
      _doc.Accept(writer);
      os << sb.GetString();
    }
}

template<>
void JSONDoc::serialize<Bomberman::Score>(const Bomberman::Score &obj)
{
  std::list<std::string> names = obj.getNames();
  if (!_doc.IsObject())
    _doc.SetObject();

  std::for_each(names.cbegin(), names.cend(), [this, &obj] (const std::string& value) {
    rapidjson::Value arr(rapidjson::kArrayType);
    std::for_each(obj.getScore(value).begin(), obj.getScore(value).end(), [this, &arr] (unsigned int score) {
      arr.PushBack(score, _doc.GetAllocator());
    });
    _doc.AddMember(value.c_str(), arr, _doc.GetAllocator());
  });
}

template<>
Bomberman::Score JSONDoc::unserialize<Bomberman::Score>() const
{
  Bomberman::Score scores;

  if (_doc.IsObject())
    {
      std::for_each(_doc.MemberBegin(), _doc.MemberEnd(), [&scores] (const rapidjson::Value::Member& player) {
	if (player.value.IsArray())
	  std::for_each(player.value.Begin(), player.value.End(), [&player, &scores] (const rapidjson::Value& score) {
	    scores.addScore(player.name.GetString(), score.GetUint());
	  });
      });
    }
  return scores;
}
