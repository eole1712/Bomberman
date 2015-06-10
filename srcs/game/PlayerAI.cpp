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
  void			PlayerAI::doAction()
  {
    if (_aiAction == NULL)
      throw std::runtime_error("AI's action is not set");
    try
      {
	(*_aiAction)(this);
      }
    catch (luabridge::LuaException const& e)
      {
	std::cerr << "Error: AI: " << e.what() << std::endl;
	throw ;
      }
  }

bool			PlayerAI::moveUp(float const & elsapsedTime, unsigned int x, unsigned int y)
{
  static glm::vec2	pos = glm::vec2(-1, -1);
  glm::vec2 		savepos;
  glm::vec2 		newpos;

  if (x != pos.x || y != pos.y)
    pos = glm::vec2(x, y);
  savepos = glm::vec2(getfX(), getfY());
  if (getX() == pos.x &&
      getY() == pos.y)
    return true;
  move(0, elsapsedTime);
  newpos = glm::vec2(getfX(), getfY());
  if ((pos - savepos).length() < (pos - newpos).length())
    {
      setPosition(glm::vec3(savepos[0], 0, savepos[1]));
      return true;
    }
  if (getRotation().y != 0)
    rotate((getRotation().y > 180), elsapsedTime, 0);
  return (false);
}

bool			PlayerAI::moveRight(float const & elsapsedTime, unsigned int x, unsigned int y)
{
  static glm::vec2	pos = glm::vec2(-1, -1);
  glm::vec2 		savepos;
  glm::vec2 		newpos;

  if (x != pos.x || y != pos.y)
    pos = glm::vec2(x, y);
  savepos = glm::vec2(getfX(), getfY());
  if (getX() == pos.x &&
      getY() == pos.y)
    return true;
  move(90, elsapsedTime);
  newpos = glm::vec2(getfX(), getfY());
  if ((pos - savepos).length() < (pos - newpos).length())
    {
      setPosition(glm::vec3(savepos[0], 0, savepos[1]));
      return true;
    }
  if (getRotation().y != 90)
    rotate((getRotation().y < 90 || getRotation().y > 270), elsapsedTime, 90);
  return false;
}

bool			PlayerAI::moveDown(float const & elsapsedTime, unsigned int x, unsigned int y)
{
  static glm::vec2	pos = glm::vec2(-1, -1);
  glm::vec2 		savepos;
  glm::vec2 		newpos;

  if (x != pos.x || y != pos.y)
    pos = glm::vec2(x, y);
  savepos = glm::vec2(getfX(), getfY());
  if (getX() == pos.x &&
      getY() == pos.y)
    return true;
  move(180, elsapsedTime);
  newpos = glm::vec2(getfX(), getfY());
  if ((pos - savepos).length() < (pos - newpos).length())
    {
      setPosition(glm::vec3(savepos[0], 0, savepos[1]));
      return true;
    }
  if (getRotation().y != 180)
    rotate((getRotation().y < 180), elsapsedTime, 180);
  return false;
}

bool			PlayerAI::moveLeft(float const & elsapsedTime, unsigned int x, unsigned int y)
{
  static glm::vec2	pos = glm::vec2(-1, -1);
  glm::vec2 		savepos;
  glm::vec2 		newpos;

  if (x != pos.x || y != pos.y)
    pos = glm::vec2(x, y);
  savepos = glm::vec2(getfX(), getfY());
  if (getX() == pos.x &&
      getY() == pos.y)
    return true;
  move(270, elsapsedTime);
  newpos = glm::vec2(getfX(), getfY());
  if ((pos - savepos).length() < (pos - newpos).length())
    {
      setPosition(glm::vec3(savepos[0], 0, savepos[1]));
      return true;
    }
  if (getRotation().y != 270)
    rotate((getRotation().y < 270 && getRotation().y >= 90), elsapsedTime, 270);
  return false;
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
      .addFunction("putBomb", &PlayerAI::putBomb) /* + move + rotate ? */
      .endClass()
      .deriveClass<PlayerAI, Player>("PlayerAI")
      .addProperty("aiName", &PlayerAI::getAIName)
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
