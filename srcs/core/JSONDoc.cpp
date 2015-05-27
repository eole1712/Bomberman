#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include "stringbuffer.h"
#include "writer.h"
#include "document.h"
#include "prettywriter.h"
#include "JSONDoc.hpp"
#include "BuffFactory.hpp"
#include "IBuff.hpp"
#include "Map.hpp"
#include "BombTimer.hpp"

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

bool		JSONDoc::parse(const std::string &name)
{
  std::ifstream is;
  std::string	str;

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

void		JSONDoc::writeDown(const std::string &filename)
{
  std::ofstream os(filename);

  if (os.good())
    {
      rapidjson::StringBuffer				sb;
      rapidjson::PrettyWriter<rapidjson::StringBuffer>	writer(sb);
      _doc.Accept(writer);
      os << sb.GetString();
    }
}

template<>
void				JSONDoc::serialize<Bomberman::Score>(const Bomberman::Score &obj)
{
  std::list<std::string>	names = obj.getNames();
  rapidjson::Value		object(rapidjson::kObjectType);

  if (!_doc.IsObject())
    _doc.SetObject();
  std::for_each(names.cbegin(), names.cend(), [this, &object, &obj] (const std::string& value) {
    rapidjson::Value arr(rapidjson::kArrayType);
    std::for_each(obj.getScore(value).begin(), obj.getScore(value).end(), [this, &arr] (unsigned int score) {
      arr.PushBack(score, _doc.GetAllocator());
    });
    object.AddMember(value.c_str(), arr, _doc.GetAllocator());
  });
  _doc.AddMember("Scores", object, _doc.GetAllocator());
}

template<>
Bomberman::Score		JSONDoc::unserialize<Bomberman::Score>(std::string const&) const
{
  Bomberman::Score		scores;

  if (_doc.IsObject() && _doc.HasMember("Scores"))
    {
      rapidjson::Value const& object(_doc["Scores"]);
      std::for_each(object.MemberBegin(), object.MemberEnd(), [&scores] (const rapidjson::Value::Member& player) {
	if (player.value.IsArray())
	  std::for_each(player.value.Begin(), player.value.End(), [&player, &scores] (const rapidjson::Value& score) {
	    scores.addScore(player.name.GetString(), score.GetUint());
	  });
      });
    }
  return scores;
}

template<>
void						JSONDoc::serialize<Bomberman::Player>(const Bomberman::Player &obj)
{
  std::list<Bomberman::BuffTimer*> const&	buffList = obj.getBuffList();

  if (!_doc.IsObject())
    _doc.SetObject();
  if (!_doc.HasMember("Players"))
    {
      rapidjson::Value playArray(rapidjson::kArrayType);
      _doc.AddMember("Players", playArray, _doc.GetAllocator());
    }
  rapidjson::Value player(rapidjson::kObjectType);
  player.AddMember("name", obj.getName().c_str(), _doc.GetAllocator());
  player.AddMember("xPos", obj.getX(), _doc.GetAllocator());
  player.AddMember("yPos", obj.getY(), _doc.GetAllocator());
  if (!buffList.empty())
    {
      rapidjson::Value buffArray(rapidjson::kArrayType);
      std::for_each(buffList.begin(), buffList.end(), [this, &player, &buffArray] (Bomberman::BuffTimer* buff) {
	rapidjson::Value object(rapidjson::kObjectType);

	object.AddMember("type", (new std::string(buff->getBuff()->getClassName()))->c_str()
			 , _doc.GetAllocator());
	object.AddMember("time", buff->getElapsedTime(), _doc.GetAllocator());
	buffArray.PushBack(object, _doc.GetAllocator());
      });
      player.AddMember("buffs", buffArray, _doc.GetAllocator());
    }
  if (_doc["Players"].IsArray())
    _doc["Players"].PushBack(player, _doc.GetAllocator());
}

template<>
Bomberman::Player*				JSONDoc::unserialize<Bomberman::Player*>(std::string const& name) const
{
  if (_doc.IsObject() && _doc.HasMember("Players"))
    {
      rapidjson::Value const& object(_doc["Players"]);
      for (rapidjson::Value::ConstValueIterator it = object.Begin(); it != object.End(); ++it)
      {
	const rapidjson::Value& player = *it;
	if (std::string(player["name"].GetString()) == name)
	  {
	    std::cout << "Name ok" << std::endl;
	    try {
	      Bomberman::Player* ret = new Bomberman::Player(player["name"].GetString(), player["xPos"].GetUint(), player["yPos"].GetUint());
	      SmartFactory<Bomberman::IBuff>* fac = Bomberman::Buff::Factory::getInstance();
	      std::for_each(player["buffs"].Begin(), player["buffs"].End(), [&ret, &fac] (rapidjson::Value const& obj) {
		Bomberman::IBuff* buff = fac->generate(obj["type"].GetString());

		if (buff->getDuration() != Bomberman::IBuff::infinite)
		  ret->addTimedBuff(new Bomberman::BuffTimer(buff, obj["time"].GetUint()));
		else
		  ret->addBuff(buff);
	      });
	      return ret;
	    }
	    catch (...)
	      {
		std::cerr << "Bad file format, do not modify the files by hand !" << std::endl;
	      }
	  }
      }
    }
  return NULL;
}

template<>
void					JSONDoc::serialize<Bomberman::Map>(Bomberman::Map const& obj)
{
  static std::function<void(unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value&)> func_tab[] =
    {
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::BombTimer* bomb = dynamic_cast<Bomberman::BombTimer*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "bomb", _doc.GetAllocator());
	cube.AddMember("typeId", 0, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("timer", bomb->getElapsedTime(), _doc.GetAllocator());
	cube.AddMember("bombType", bomb->getBombType(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "player", _doc.GetAllocator());
	cube.AddMember("typeId", 1, _doc.GetAllocator());
	cube.AddMember("name", dynamic_cast<Bomberman::Player*>(obj)->getName().c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "bonus", _doc.GetAllocator());
	cube.AddMember("typeId", 2, _doc.GetAllocator());
	cube.AddMember("bonusType", dynamic_cast<Bomberman::IBuff*>(obj)->getBuffType(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "wall", _doc.GetAllocator());
	cube.AddMember("typeId", 3, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "destrWall", _doc.GetAllocator());
	cube.AddMember("typeId", 4, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
       [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "spawn", _doc.GetAllocator());
	cube.AddMember("typeId", 5, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
       [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "empty", _doc.GetAllocator());
	cube.AddMember("typeId", 6, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      }
    };

  rapidjson::Value			object(rapidjson::kObjectType);
  rapidjson::Value			array(rapidjson::kArrayType);
  Bomberman::IObject*			cellValue;

  if (!_doc.IsObject())
    _doc.SetObject();
  object.AddMember("name", obj.getName().c_str(), _doc.GetAllocator());
  object.AddMember("nbPlayers", obj.getNumberPlayers(), _doc.GetAllocator());
  object.AddMember("difficulty", obj.getDiff(), _doc.GetAllocator());
  object.AddMember("width", obj.getWidth(), _doc.GetAllocator());
  object.AddMember("height", obj.getHeight(), _doc.GetAllocator());
  for (unsigned int x = 0; x < obj.getWidth(); ++x) {
    for (unsigned int y = 0; y < obj.getHeight(); ++y)
      {
	cellValue = obj.getCellValue(x, y);
	func_tab[cellValue->getObjectType()](x, y, cellValue, array);
      }
  }
  object.AddMember("cases", array, _doc.GetAllocator());
  _doc.AddMember("map", object, _doc.GetAllocator());
}
