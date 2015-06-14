#include <fstream>
#include <functional>
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
#include "BombFactory.hpp"
#include "Wall.hpp"
#include "DestroyableWall.hpp"
#include "Spawn.hpp"
#include "Empty.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson.h"
#include "PlayerAI.hpp"

// #undef RAPIDJSON_ASSERT
//#define RAPIDJSON_ASSERT(x) dynamic_cast<std::string>(x)->empty()

JSONDoc::JSONDoc()
{
  _doc.SetObject();
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
  //writeDown(_filename);
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
      if (_doc.HasParseError()) {
    	std::cerr << "JSON parse error: " << _doc.GetParseError() << " at : " << _doc.GetErrorOffset() << std::endl;
	return false;
      }
      _filename = name;
      return true;
    }
  return false;
}

void		JSONDoc::writeDown(const std::string &filename)
{
  std::ofstream os(filename, std::fstream::out | std::fstream::trunc);

  if (os.good())
    {
      rapidjson::StringBuffer				sb;
      rapidjson::Writer<rapidjson::StringBuffer>	writer(sb);
      _doc.Accept(writer);
      os << sb.GetString();
    }
  else
    {
      std::cout << "failed to write" << std::endl;
    }
}

template<>
void				JSONDoc::serialize<Bomberman::ScoreList>(const Bomberman::ScoreList &obj)
{
  std::list<std::string>	names = obj.getNames();
  rapidjson::Value		object(rapidjson::kObjectType);


  while (_doc.HasMember("Scores"))
    _doc.RemoveMember("Scores");
  std::for_each(names.cbegin(), names.cend(), [this, &object, &obj] (const std::string& value) {
    rapidjson::Value arr(rapidjson::kArrayType);
    std::for_each(obj.getScore(value).begin(), obj.getScore(value).end(), [this, &arr] (unsigned int score) {
      arr.PushBack(score, _doc.GetAllocator());
    });
    object.AddMember(value.c_str() , arr, _doc.GetAllocator());
  });
  _doc.AddMember("Scores", object, _doc.GetAllocator());
}

template<>
Bomberman::ScoreList*		JSONDoc::unserialize<Bomberman::ScoreList*>(std::string const&) const
{
  Bomberman::ScoreList*		scores = new Bomberman::ScoreList;

  if (_doc.HasMember("Scores"))
    {
      rapidjson::Value const& object(_doc["Scores"]);
      std::for_each(object.MemberBegin(), object.MemberEnd(), [&scores] (const rapidjson::Value::Member& player) {
	if (player.value.IsArray())
	  std::for_each(player.value.Begin(), player.value.End(), [&player, &scores] (const rapidjson::Value& score) {
	    scores->addScore(player.name.GetString(), score.GetUint());
	  });
      });
    }
  return scores;
}

template<>
void		JSONDoc::serialize<Bomberman::MapList>(const Bomberman::MapList &obj)
{
  std::unordered_map<std::string, std::pair<unsigned int, unsigned int> > list = obj.getMapList();
  rapidjson::Value		object(rapidjson::kObjectType);

  while (_doc.HasMember("Maps"))
    _doc.RemoveMember("Maps");
  if (!_doc.IsObject())
    _doc.SetObject();
  std::for_each(list.cbegin(), list.cend(), [this, &obj, &object] (std::pair<std::string, std::pair<unsigned int, unsigned int> > const& value) {
    rapidjson::Value		members(rapidjson::kObjectType);
    members.AddMember("width", value.second.first, _doc.GetAllocator());
    members.AddMember("height", value.second.second, _doc.GetAllocator());
    object.AddMember(value.first.c_str(), members, _doc.GetAllocator());
  });
  _doc.AddMember("Maps", object, _doc.GetAllocator());
}

template<>
Bomberman::MapList*		JSONDoc::unserialize<Bomberman::MapList*>(std::string const&) const
{
  Bomberman::MapList*		list = new Bomberman::MapList;

  if (_doc.IsObject() && _doc.HasMember("Maps"))
    {
      rapidjson::Value const& object(_doc["Maps"]);
      std::for_each(object.MemberBegin(), object.MemberEnd(), [&list] (const rapidjson::Value::Member& map) {
	if (map.value.IsObject() && map.value.HasMember("height"),
	    map.value.HasMember("width"))
	  list->addMap(map.name.GetString(), map.value["width"].GetUint(), map.value["height"].GetUint());
      });
    }
  return list;
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
  player.AddMember("xPos", obj.getfX(), _doc.GetAllocator());
  player.AddMember("yPos", obj.getfY(), _doc.GetAllocator());
  player.AddMember("red", obj.getColor()[0], _doc.GetAllocator());
  player.AddMember("green", obj.getColor()[1], _doc.GetAllocator());
  player.AddMember("blue", obj.getColor()[2], _doc.GetAllocator());
  player.AddMember("IA", true, _doc.GetAllocator());
  if (!buffList.empty())
    {
      rapidjson::Value buffArray(rapidjson::kArrayType);
      std::for_each(buffList.begin(), buffList.end(), [this, &player, &buffArray] (Bomberman::BuffTimer* buff) {
	rapidjson::Value object(rapidjson::kObjectType);

	object.AddMember("type", (new std::string(buff->getBuff()->getClassName()))->c_str()
			 , _doc.GetAllocator());
	object.AddMember("time", 5.0 - (buff->getElapsedTime() / 10000000), _doc.GetAllocator());
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
	    try {
	      Bomberman::Player* ret = new Bomberman::Player(player["name"].GetString(), glm::vec4(player["red"].GetDouble(),
												   player["green"].GetDouble(), player["blue"].GetDouble(), 0));
	      ret->setPosition(glm::vec3(player["xPos"].GetDouble(), 0, player["yPos"].GetDouble()));
	      SmartFactory<Bomberman::IBuff>* fac = Bomberman::Buff::Factory::getInstance();
	      if (player.HasMember("buffs"))
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
	//_doc["Players"].Erase(it);
      }
    }
  return NULL;
}

template<>
void					JSONDoc::serialize<Bomberman::Map>(Bomberman::Map const& obj)
{
  static std::function<void(unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value&)> func_tab[] =
    {
      [] (unsigned int, unsigned int, Bomberman::IObject*, rapidjson::Value&) -> void {
	throw std::runtime_error("Player on map");
	// rapidjson::Value cube(rapidjson::kObjectType);
      	// cube.AddMember("posX", x, _doc.GetAllocator());
      	// cube.AddMember("posY", y, _doc.GetAllocator());
      	// cube.AddMember("type", "player", _doc.GetAllocator());
      	// cube.AddMember("typeId", 1, _doc.GetAllocator());
      	// cube.AddMember("name", dynamic_cast<Bomberman::Player*>(obj)->getName().c_str(), _doc.GetAllocator());
      	// map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "bonus", _doc.GetAllocator());
	cube.AddMember("typeId", 1, _doc.GetAllocator());
	std::string* type = new std::string(dynamic_cast<Bomberman::IBuff*>(obj)->getClassName().c_str());
	cube.AddMember("bonusType", type->c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "wall", _doc.GetAllocator());
	cube.AddMember("typeId", 2, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "destrWall", _doc.GetAllocator());
	cube.AddMember("typeId", 3, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "spawn", _doc.GetAllocator());
	cube.AddMember("typeId", 4, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject*, rapidjson::Value& map) -> void {
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "empty", _doc.GetAllocator());
	cube.AddMember("typeId", 5, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::Fire* bomb = dynamic_cast<Bomberman::Fire*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "fire", _doc.GetAllocator());
	cube.AddMember("typeId", 6, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("id", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getId(), _doc.GetAllocator());
	cube.AddMember("timer", 5.0 - (bomb->getElapsedTime() / 10000000), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::BombTimer* bomb = dynamic_cast<Bomberman::BombTimer*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "mine", _doc.GetAllocator());
	cube.AddMember("typeId", 7, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("id", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getId(), _doc.GetAllocator());
	cube.AddMember("range", bomb->getRange(), _doc.GetAllocator());
	cube.AddMember("timer", 5.0 - (bomb->getElapsedTime() / 10000000), _doc.GetAllocator());
	std::string* type = new std::string(bomb->getBombType()->getClassName());
	cube.AddMember("bombType", type->c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::BombTimer* bomb = dynamic_cast<Bomberman::BombTimer*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "bomb", _doc.GetAllocator());
	cube.AddMember("typeId", 8, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("id", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getId(), _doc.GetAllocator());
	cube.AddMember("range", bomb->getRange(), _doc.GetAllocator());
	cube.AddMember("timer", 5.0 - (bomb->getElapsedTime() / 10000000), _doc.GetAllocator());
	std::string* type = new std::string(bomb->getBombType()->getClassName());
	cube.AddMember("bombType", type->c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::BombTimer* bomb = dynamic_cast<Bomberman::BombTimer*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "barrel", _doc.GetAllocator());
	cube.AddMember("typeId", Bomberman::IObject::BOMB, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("id", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getId(), _doc.GetAllocator());
	cube.AddMember("range", bomb->getRange(), _doc.GetAllocator());
	cube.AddMember("timer", 5.0 - (bomb->getElapsedTime() / 10000000), _doc.GetAllocator());
	std::string* type = new std::string(bomb->getBombType()->getClassName());
	cube.AddMember("bombType", type->c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::BombTimer* bomb = dynamic_cast<Bomberman::BombTimer*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "barrel", _doc.GetAllocator());
	cube.AddMember("typeId", Bomberman::IObject::BARREL, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("id", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getId(), _doc.GetAllocator());
	cube.AddMember("range", bomb->getRange(), _doc.GetAllocator());
	cube.AddMember("timer", 5.0 - (bomb->getElapsedTime() / 10000000), _doc.GetAllocator());
	std::string* type = new std::string(bomb->getBombType()->getClassName());
	cube.AddMember("bombType", type->c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
      [this] (unsigned int x, unsigned int y, Bomberman::IObject* obj, rapidjson::Value& map) -> void {
	Bomberman::BombTimer* bomb = dynamic_cast<Bomberman::BombTimer*>(obj);
	rapidjson::Value cube(rapidjson::kObjectType);
	cube.AddMember("posX", x, _doc.GetAllocator());
	cube.AddMember("posY", y, _doc.GetAllocator());
	cube.AddMember("type", "barrel", _doc.GetAllocator());
	cube.AddMember("typeId", Bomberman::IObject::VIRUS, _doc.GetAllocator());
	cube.AddMember("owner", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getName().c_str(), _doc.GetAllocator());
	cube.AddMember("id", dynamic_cast<Bomberman::Player*>(bomb->getPlayer())->getId(), _doc.GetAllocator());
	cube.AddMember("range", bomb->getRange(), _doc.GetAllocator());
	cube.AddMember("timer", 5.0 - (bomb->getElapsedTime() / 10000000), _doc.GetAllocator());
	std::string* type = new std::string(bomb->getBombType()->getClassName());
	cube.AddMember("bombType", type->c_str(), _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
	map.PushBack(cube, _doc.GetAllocator());
      },
    };

  rapidjson::Value			object(rapidjson::kObjectType);
  rapidjson::Value			array(rapidjson::kArrayType);
    rapidjson::Value			mapArray(rapidjson::kArrayType);
  Bomberman::IObject*			cellValue;

  if (!_doc.IsObject())
    _doc.SetObject();
  if (_doc.HasMember("map"))
    _doc.RemoveMember("map");
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
  mapArray.PushBack(object, _doc.GetAllocator());
  _doc.AddMember("map", mapArray, _doc.GetAllocator());

}

template<>
Bomberman::Map*				JSONDoc::unserialize<Bomberman::Map*>(std::string const& name) const
{
  std::vector<Bomberman::Player*>	players;
  Bomberman::Map* mapPtr = NULL;
  static const std::function<Bomberman::IObject*(rapidjson::Value const&)> func_tab[] =
    {
      [] (rapidjson::Value const&) -> Bomberman::IObject* {
	std::cout << "pas normal ca" << std::endl;
	return NULL;
      },
      [] (rapidjson::Value const& obj) -> Bomberman::IObject* {
      	SmartFactory<Bomberman::IBuff>* fac = Bomberman::Buff::Factory::getInstance();
	Bomberman::IBuff* buff;
	if ((buff = fac->generate(obj["bonusType"].GetString())) == NULL)
	  return fac->generate("Weapon");
	return buff;
      },
      [] (rapidjson::Value const&) -> Bomberman::IObject* {
	return new Bomberman::Wall();
      },
      [] (rapidjson::Value const&) -> Bomberman::IObject* {
	return new Bomberman::DestroyableWall();
      },
      [] (rapidjson::Value const&) -> Bomberman::IObject* {
	return new Bomberman::Spawn();
      },
      [] (rapidjson::Value const&) -> Bomberman::IObject* {
	return new Bomberman::Empty();
      },
      [this, &players, &mapPtr] (rapidjson::Value const& obj) -> Bomberman::IObject* {
	Bomberman::Player* player = NULL;
	unsigned int i = 0;
	for (std::vector<Bomberman::Player*>::iterator it =  players.begin(); it != players.end(); ++it)
	  {
	    if (!obj.HasMember("id"))
	      player = NULL;
	    else if (obj["id"].GetUint() == i)
	      player = (*it);
	    ++i;
	  }
	Bomberman::Fire* fTimer = new Bomberman::Fire(player, obj["posX"].GetUint(), obj["posY"].GetUint(), obj["timer"].GetUint());
	mapPtr->addFire(fTimer);
	return fTimer;
      },
      [this, &players, &mapPtr] (rapidjson::Value const& obj) -> Bomberman::IObject* {
	Bomberman::Player* player = NULL;
	unsigned int i = 0;
	SmartFactory<Bomberman::IBomb>*	fac = Bomberman::Bomb::Factory::getInstance();
	for (std::vector<Bomberman::Player*>::iterator it =  players.begin(); it != players.end(); ++it)
	  {
	    if (!obj.HasMember("id"))
	      player = NULL;
	    else if (obj["id"].GetUint() == i)
	      player = (*it);
	    ++i;
	  }
	Bomberman::IBomb* bomb = fac->generate(obj["bombType"].GetString());
	if (bomb == NULL)
	  bomb = fac->generate("Classic");
	Bomberman::BombTimer* bTimer = new Bomberman::BombTimer(player, obj["range"].GetUint(), bomb, obj["timer"].GetUint(), obj["posX"].GetUint(), obj["posY"].GetUint(), false);
	mapPtr->addBomb(bTimer);
	return bTimer;
      },
      [this, &players, &mapPtr] (rapidjson::Value const& obj) -> Bomberman::IObject* {
	Bomberman::Player* player = NULL;
	unsigned int i = 0;
	SmartFactory<Bomberman::IBomb>*	fac = Bomberman::Bomb::Factory::getInstance();
	for (std::vector<Bomberman::Player*>::iterator it =  players.begin(); it != players.end(); ++it)
	  {
	    if (!obj.HasMember("id"))
	      player = NULL;
	    else if (obj["id"].GetUint() == i)
	      player = (*it);
	    ++i;
	  }
	Bomberman::IBomb* bomb = fac->generate(obj["bombType"].GetString());
	if (bomb == NULL)
	  bomb = fac->generate("Classic");
	Bomberman::BombTimer* bTimer = new Bomberman::BombTimer(player, obj["range"].GetUint(), bomb, obj["timer"].GetUint(), obj["posX"].GetUint(), obj["posY"].GetUint(), false);
	mapPtr->addBomb(bTimer);
	return bTimer;
      },
	[this, &players, &mapPtr] (rapidjson::Value const& obj) -> Bomberman::IObject* {
	Bomberman::Player* player = NULL;
	unsigned int i = 0;
	SmartFactory<Bomberman::IBomb>*	fac = Bomberman::Bomb::Factory::getInstance();
	for (std::vector<Bomberman::Player*>::iterator it =  players.begin(); it != players.end(); ++it)
	  {
	    if (!obj.HasMember("id"))
	      player = NULL;
	    else if (obj["id"].GetUint() == i)
	      player = (*it);
	    ++i;
	  }
	Bomberman::IBomb* bomb = fac->generate(obj["bombType"].GetString());
	if (bomb == NULL)
	  bomb = fac->generate("Classic");
	Bomberman::BombTimer* bTimer = new Bomberman::BombTimer(player, obj["range"].GetUint(), bomb, obj["timer"].GetUint(), obj["posX"].GetUint(), obj["posY"].GetUint(), false);
	mapPtr->addBomb(bTimer);
	return bTimer;
	},
	[this, &players, &mapPtr] (rapidjson::Value const& obj) -> Bomberman::IObject* {
	Bomberman::Player* player = NULL;
	unsigned int i = 0;
	SmartFactory<Bomberman::IBomb>*	fac = Bomberman::Bomb::Factory::getInstance();
	for (std::vector<Bomberman::Player*>::iterator it =  players.begin(); it != players.end(); ++it)
	  {
	    if (!obj.HasMember("id"))
	      player = NULL;
	    else if (obj["id"].GetUint() == i)
	      player = (*it);
	    ++i;
	  }
	Bomberman::IBomb* bomb = fac->generate(obj["bombType"].GetString());
	if (bomb == NULL)
	  bomb = fac->generate("Classic");
	Bomberman::BombTimer* bTimer = new Bomberman::BombTimer(player, obj["range"].GetUint(), bomb, obj["timer"].GetUint(), obj["posX"].GetUint(), obj["posY"].GetUint(), false);
	mapPtr->addBomb(bTimer);
	return bTimer;
      }
    };

  if (_doc.HasMember("Players"))
    {
      rapidjson::Value const& plays = _doc["Players"];
      for (rapidjson::Value::ConstValueIterator it = plays.Begin(); it != plays.End(); ++it)
	{
	  players.push_back(unserialize<Bomberman::Player*>((*it)["name"].GetString()));
	}
    }
  if (_doc.IsObject() && _doc.HasMember("map"))
    {
      rapidjson::Value const& mapsArray = _doc["map"];
      for (rapidjson::Value::ConstValueIterator it = mapsArray.Begin(); it != mapsArray.End(); ++it)
	{
	  if (name == "" || (*it)["name"].GetString() == name)
	    {
	      rapidjson::Value const& mapObj = (*it);
	      mapPtr = new Bomberman::Map(mapObj["name"].GetString(), mapObj["width"].GetUint(), mapObj["height"].GetUint(), mapObj["nbPlayers"].GetUint(), static_cast<Bomberman::Map::e_difficulty>(mapObj["difficulty"].GetUint()));
	      rapidjson::Value const& mapArray = mapObj["cases"];
	      std::for_each(mapArray.Begin(), mapArray.End(), [mapPtr] (rapidjson::Value const& row) {
		Bomberman::IObject* elem = func_tab[row["typeId"].GetUint()](row);
		mapPtr->setCellValue(row["posX"].GetUint(), row["posY"].GetUint(), elem);
	      });
	      return mapPtr;
	    }
	}
    }
  return NULL;
}


template<>
void	JSONDoc::serialize(const Bomberman::Gamer& obj)
{
  Bomberman::RessourceStock*	rs;
  Bomberman::Map*		map;

  if (_doc.HasMember("Players"))
    _doc.RemoveMember("Players");
  rs = obj.getRessourceStock();
  map = obj.getMap();
  for (unsigned int i = 0; i < rs->getNbPlayer(); ++i)
    {
      serialize<Bomberman::Player>(*rs->getPlayer(i));
      rs->getPlayer(i)->setId(i);
      if (!rs->getPlayer(i)->isIA())
	{
	  rapidjson::Value & object(_doc["Players"]);
	  for (rapidjson::Value::ValueIterator it = object.Begin(); it != object.End(); ++it)
	    {
	      rapidjson::Value& player = *it;
	      if (!player.HasMember("id"))
		{
		  player.AddMember("id", i, _doc.GetAllocator());
		}
	      if (player.HasMember("name") && player["name"].GetString() == rs->getPlayer(i)->getName() && player.HasMember("IA"))
		player["IA"] = false;
	    }
	}
    }
  serialize(*map);
  writeDown("resources/SavedDatas.json");
}

template <>
Bomberman::Gamer *JSONDoc::unserialize<Bomberman::Gamer*>(std::string const&) const
{
  Bomberman::Gamer* game;
  Bomberman::Map* map = unserialize<Bomberman::Map*>("");
  Bomberman::ScoreList* scoreList = unserialize<Bomberman::ScoreList*>("");
  std::vector<Bomberman::Player*> players;
  Bomberman::RessourceStock* rc;
  int nbPlayers = 0;
  JSONDoc j;
  Bomberman::ScoreList* sList;

  if (_doc.HasMember("Players"))
    {
      std::cout << "yolo" << std::endl;
      rapidjson::Value const& plays = _doc["Players"];
      for (rapidjson::Value::ConstValueIterator it = plays.Begin(); it != plays.End(); ++it)
	{
	  Bomberman::Player* player;
	  std::cout << "player" << std::endl;
	  if ((*it).HasMember("name"))
	    std::cout << "cool" << std::endl;
	  players.push_back((player = unserialize<Bomberman::Player*>((*it)["name"].GetString())));
	  //player->initGame(player->getX(), player->getY(), map);
	  if (!(*it)["IA"].GetBool())
	    ++nbPlayers;

	}
    }
  if (!j.parse("./resources/json/Gamedata.json"))
    sList = new Bomberman::ScoreList;
  else
    sList = j.unserialize<Bomberman::ScoreList*>();
  rc = new Bomberman::RessourceStock(players, sList);
  game = new Bomberman::Gamer(map->getWidth(), map->getHeight(), 1800, 900, (!nbPlayers == 1), "", "",
			      players.size(), map, scoreList);
  game->setRcs(rc);
  map->setRcs(rc);
  for (std::vector<Bomberman::Player*>::iterator it = players.begin(); it != players.end(); ++it)
    (*it)->initGame((*it)->getX(), (*it)->getY(), map);
  game->setMap(map);
  std::cout << "rcs init : " << map->getRcs() << std::endl;
  return game;
}
