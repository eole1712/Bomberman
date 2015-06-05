#include <iostream>
#include "PlayerAI.hpp"
#include "LuaError.hpp"
#include "AIStateMap.hpp"

namespace Bomberman
{
  /*
  ** Constructor/Destructor
  */
  PlayerAI::PlayerAI(std::string const& name, std::string const& script) :
    Player() /* tmp */, LuaScript(script), _aiAction(NULL)
  {
    luaObjectInit();
    run();
    loadAIData();
    static_cast<void>(name);
  }

  PlayerAI::PlayerAI(std::string const& name,
		     std::string const& script, glm::vec4 color) :
    Player(name, color), LuaScript(script), _aiAction(NULL)
  {
    luaObjectInit();
    run();
    loadAIData();
  }

  PlayerAI::~PlayerAI()
  {
    if (_aiAction != NULL)
      delete (_aiAction);
  }

  /*
  ** Public member functions
  */
  void			PlayerAI::doAction(Map const& map, float const& elapsedTime)
  {
    AI::StateMap	stateMap(map);

    if (_aiAction == NULL)
      throw std::runtime_error("AI's action is not set");
    try
      {
	(*_aiAction)(this, &stateMap, elapsedTime);
      }
    catch (luabridge::LuaException const& e)
      {
	std::cerr << "Error: AI: " << e.what() << std::endl;
	throw ;
      }
  }

void			PlayerAI::moveUp(float const& elsapsedTime)
{
  move(0, elsapsedTime);
  if (getRotation().y != 0)
    rotate((getRotation().y > 180), elsapsedTime, 0);
}

  void			PlayerAI::moveRight(float const& elsapsedTime)
  {
    move(270, elsapsedTime);
    if (getRotation().y != 270)
      rotate((getRotation().y < 270 && getRotation().y >= 90), elsapsedTime, 270);
  }

  void			PlayerAI::moveDown(float const& elsapsedTime)
  {

    move(180, elsapsedTime);
    if (getRotation().y != 180)
      rotate((getRotation().y < 180), elsapsedTime, 180);
  }

  void			PlayerAI::moveLeft(float const& elsapsedTime)
  {
    move(90, elsapsedTime);
    if (getRotation().y != 90)
      rotate((getRotation().y < 90 || getRotation().y > 270), elsapsedTime, 90);
  }

  std::string const&	PlayerAI::getAIName() const
  {
    return (_aiName);
  }

  /*
  ** Protected member functions
  */
  void			PlayerAI::luaObjectInit()
  {
    getGlobalNamespace(_state)
      .beginClass<Player>("Player")
      .addConstructor<void (*)(void)>()
      .addProperty("isAlive", &PlayerAI::isAlive)
      .addProperty("isParalyzed", &PlayerAI::isParalyzed)
      .addProperty("isZeroBomb", &PlayerAI::zeroBomb)
      .addProperty("range", &PlayerAI::getRange)
      .addProperty("speed", &PlayerAI::getSpeed)
      .addProperty("nbBomb", &PlayerAI::getNbBomb)
      .addProperty("bombType", &PlayerAI::getBombType)
      .addProperty("x", &PlayerAI::getX)
      .addProperty("y", &PlayerAI::getY)
      .addFunction("putBomb", &PlayerAI::putBomb)
      .endClass()
      .deriveClass<PlayerAI, Player>("PlayerAI")
      .addProperty("aiName", &PlayerAI::getAIName)
      .addFunction("moveRight", &PlayerAI::moveRight)
      .addFunction("moveLeft", &PlayerAI::moveLeft)
      .addFunction("moveUp", &PlayerAI::moveUp)
      .addFunction("moveDown", &PlayerAI::moveDown)
      .endClass()
      .beginClass<GenericMap<AI::Cell> >("GenericMap")
      .addProperty("width", &GenericMap<AI::Cell>::getWidth)
      .addProperty("height", &GenericMap<AI::Cell>::getHeight)
      .addFunction("getCell", &GenericMap<AI::Cell>::getCellValue)
      .endClass()
      .beginClass<AI::StateMap>("StateMap")
      .addFunction("toString", &AI::StateMap::toString)
      .addFunction("getPlayerPosX", &AI::StateMap::getPlayerPosX)
      .addFunction("getPlayerPosY", &AI::StateMap::getPlayerPosY)
      .addFunction("getNbPlayers", &AI::StateMap::getNbPlayers)
      .endClass();
  }

  void			PlayerAI::loadAIData()
  {
    luabridge::LuaRef	data = getGlobal(_state, "aiData");

    if (!data.isTable())
      throw Exception::LuaError("aiData is not a table");
    if (!data["name"].isString())
      throw Exception::LuaError("name specified in aiData is not a string");
    _aiName = data["name"].cast<std::string>();
    if (!data["aiAction"].isFunction())
      throw Exception::LuaError("aiAction specified in aiData is not a function");
    _aiAction = new luabridge::LuaRef(data["aiAction"]);
  }
}
