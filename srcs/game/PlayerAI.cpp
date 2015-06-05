#include <iostream>
#include "PlayerAI.hpp"
#include "LuaError.hpp"

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

  PlayerAI::~PlayerAI()
  {
    if (_aiAction != NULL)
      delete (_aiAction);
  }

  /*
  ** Public member functions
  */
  void			PlayerAI::doAction(float const& elapsedTime)
  {
    if (_aiAction == NULL)
      throw std::runtime_error("AI's action is not set");
    try
      {
	(*_aiAction)(this, elapsedTime);
      }
    catch (luabridge::LuaException const& e)
      {
	std::cerr << "Error: AI: " << e.what() << std::endl;
	throw ;
      }
  }

void			PlayerAI::moveUp(float const& elsapsedTime)
{
  std::cout << "meh " << elsapsedTime << std::endl;
  move(0, elsapsedTime);
  std::cout << "meh2 " << elsapsedTime << std::endl;
  if (getRotation().y != 0)
    rotate((getRotation().y > 180), elsapsedTime, 0);
}

  void			PlayerAI::moveRight(float const& elsapsedTime)
  {
    move(90, elsapsedTime);
    if (getRotation().y != 90)
      rotate((getRotation().y < 90 || getRotation().y > 270), elsapsedTime, 90);
  }

  void			PlayerAI::moveDown(float const& elsapsedTime)
  {

    move(180, elsapsedTime);
    if (getRotation().y != 180)
      rotate((getRotation().y < 180), elsapsedTime, 180);
  }

  void			PlayerAI::moveLeft(float const& elsapsedTime)
  {
    move(270, elsapsedTime);
    if (getRotation().y != 270)
      rotate((getRotation().y < 270 && getRotation().y >= 90), elsapsedTime, 270);
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
      .addFunction("putBomb", &PlayerAI::putBomb)
      .endClass()
      .deriveClass<PlayerAI, Player>("PlayerAI")
      .addProperty("aiName", &PlayerAI::getAIName)
      .addFunction("moveRight", &PlayerAI::moveRight)
      .addFunction("moveLeft", &PlayerAI::moveLeft)
      .addFunction("moveUp", &PlayerAI::moveUp)
      .addFunction("moveDown", &PlayerAI::moveDown)
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
