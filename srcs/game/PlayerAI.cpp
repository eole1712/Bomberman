#include "PlayerAI.hpp"

namespace Bomberman
{
  /*
  ** Constructor/Destructor
  */
  PlayerAI::PlayerAI(std::string const& name, std::string const& script)
    Player() /* tmp */, LuaScript(script), _aiAction(NULL)
  {
    luaObjectInit();
    static_cast<void>(name);
  }

  PlayerAI::~PlayerAI()
  {
  }

  /*
  ** Public member functions
  */
  void			PlayerAI::doAction()
  {
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
      .addConstructor<void (*)(void)>
      .addProperty("isAlive", &PlayerAI::isAlive, NULL)
      .addProperty("isParalyzed", &PlayerAI::isParalyzed, NULL)
      .addProperty("isZeroBomb", &PlayerAI::zeroBomb, NULL)
      .addProperty("range", &PlayerAI::getRange, NULL)
      .addProperty("speed", &PlayerAI::getSpeed, NULL)
      .addProperty("nbBomb", &PlayerAI::getNbBomb, NULL)
      .addProperty("bombType", &PlayerAI::getBombType, NULL)
      .addFunction("putBomb", &PlayerAI::putBomb()) /* + move + rotate ? */
      .endClass();
  }
}
