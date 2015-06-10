#include <iostream>
#include <glm/gtx/norm.hpp>
#include "PlayerAI.hpp"
#include "LuaError.hpp"
#include "AIStateMap.hpp"

namespace Bomberman
{
  /*
  ** Static variables
  */
  const PlayerAI::MoveBook	PlayerAI::moveBook	= PlayerAI::getMoveBook();

  /*
  ** Constructor/Destructor
  */
  PlayerAI::PlayerAI(std::string const& name, std::string const& script) :
    Player() /* tmp */, LuaScript(script), _aiAction(NULL), _moveDir(NONE)
  {
    luaObjectInit();
    run();
    loadAIData();
    static_cast<void>(name);
  }

  PlayerAI::PlayerAI(std::string const& name,
		     std::string const& script, glm::vec4 color) :
    Player(name, color), LuaScript(script), _aiAction(NULL), _moveDir(NONE)
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
	if (_moveDir == NONE)
	  (*_aiAction)(this, &stateMap);
	if (_moveDir != NONE)
	  {
	    if ((this->*(moveBook.at(_moveDir)))(elapsedTime))
	      {
		std::cout << "end moving" << std::endl;
		_moveDir = NONE;
	      }
	    else
	      std::cout << "moving" << std::endl;
	  }
      }
    catch (luabridge::LuaException const& e)
      {
	std::cerr << "Error: AI: " << e.what() << std::endl;
	throw ;
      }
  }

  void			PlayerAI::moveRight()
  {
    _moveDir = RIGHT;
  }

  void			PlayerAI::moveLeft()
  {
    _moveDir = LEFT;
  }

  void			PlayerAI::moveUp()
  {
    _moveDir = UP;
  }

  void			PlayerAI::moveDown()
  {
    _moveDir = DOWN;
  }

  bool			PlayerAI::isAttack() const
  {
    return (_attack);
  }

  bool			PlayerAI::isDefense() const
  {
    return (!_attack);
  }

  void			PlayerAI::memoriseAttackMode()
  {
    _attack = true;
  }

  void			PlayerAI::memoriseDefenseMode()
  {
    _attack = false;
  }

  void			PlayerAI::memoriseGoal(unsigned int x, unsigned int y)
  {
    _goal.first = x;
    _goal.second = y;
  }

  void			PlayerAI::resetGoal()
  {
    _goal.first = -1;
    _goal.second = -1;
  }

  int			PlayerAI::getGoalX() const
  {
    return (_goal.first);
  }

  int			PlayerAI::getGoalY() const
  {
    return (_goal.second);
  }

  bool			PlayerAI::moveUpCell(float const &elsapsedTime)
  {
    static bool		bra = true;
    static glm::vec2	pos;
    glm::vec2 		savepos;
    glm::vec2 		newpos;

    if (bra)
      {
	pos = glm::vec2(getfX(), getY() + 1.5);
	bra = false;
      }
    else if (getfX() == pos.x &&
	     getfY() == pos.y)
      return (bra = true);
    if (getRotation().y == 0 ||
	rotate((getRotation().y > 180), elsapsedTime, 0))
      {
	savepos = glm::vec2(getfX(), getfY());
	move(0, elsapsedTime);
	newpos = glm::vec2(getfX(), getfY());
	if (savepos.y < pos.y && newpos.y >= pos.y)
	  {
	    setPosition(glm::vec3(pos.x, 0, pos.y));
	    return (bra = true);
	  }
	if (sqrt(pow(pos.x - savepos.x,2) + pow(pos.y - savepos.y, 2)) <= sqrt(pow(pos.x - newpos.x,2) + pow(pos.y - newpos.y, 2)))
	  {
	    setPosition(glm::vec3(savepos[0], 0, savepos[1]));
	    return (bra = true);
	  }
      }
    return (false);
  }

  bool			PlayerAI::moveRightCell(float const& elsapsedTime)
  {
    static bool		bra = true;
    static glm::vec2	pos;
    glm::vec2 		savepos;
    glm::vec2 		newpos;

    if (bra)
      {
	pos = glm::vec2(getX() + 1.5, getfY());
	bra = false;
      }
    else if (getfX() == pos.x &&
	     getfY() == pos.y)
      return (bra = true);
    if (getRotation().y == 90 ||
	rotate((getRotation().y < 90 || getRotation().y > 270), elsapsedTime, 90))
      {
	savepos = glm::vec2(getfX(), getfY());
	move(90, elsapsedTime);
	newpos = glm::vec2(getfX(), getfY());
	if (savepos.x > pos.x && newpos.x <= pos.x)
	  {
	    setPosition(glm::vec3(pos.x, 0, pos.y));
	    return (bra = true);
	  }
	if (sqrt(pow(pos.x - savepos.x,2) + pow(pos.y - savepos.y, 2)) <= sqrt(pow(pos.x - newpos.x,2) + pow(pos.y - newpos.y, 2)))
	  {
	    setPosition(glm::vec3(savepos[0], 0, savepos[1]));
	    return (bra = true);
	  }
      }
    return false;
  }

  bool			PlayerAI::moveDownCell(float const& elsapsedTime)
  {
    static bool		bra = true;
    static glm::vec2	pos;
    glm::vec2 		savepos;
    glm::vec2 		newpos;

    if (bra)
      {
	pos = glm::vec2(getfX(), getY() - 1.5);
	bra = false;
      }
    else if (getfX() == pos.x &&
	     getfY() == pos.y)
      return (bra = true);
    if (getRotation().y == 180 ||
	rotate((getRotation().y < 180), elsapsedTime, 180))
      {
	savepos = glm::vec2(getfX(), getfY());
	move(180, elsapsedTime);
	newpos = glm::vec2(getfX(), getfY());
	if (savepos.y > pos.y && newpos.y <= pos.y)
	  {
	    setPosition(glm::vec3(pos.x, 0, pos.y));
	    return (bra = true);
	  }
	if (sqrt(pow(pos.x - savepos.x,2) + pow(pos.y - savepos.y, 2)) <= sqrt(pow(pos.x - newpos.x,2) + pow(pos.y - newpos.y, 2)))
	  {
	    setPosition(glm::vec3(savepos[0], 0, savepos[1]));
	    return (bra = true);
	  }
      }
    return false;
  }

  bool			PlayerAI::moveLeftCell(float const& elsapsedTime)
  {
    static bool		bra = true;
    static glm::vec2	pos;
    glm::vec2 		savepos;
    glm::vec2 		newpos;

    if (bra)
      {
	pos = glm::vec2(getX() - 1.5, getfY());
	bra = false;
      }
    else if (getfX() == pos.x &&
	     getfY() == pos.y)
      return (bra = true);
    if (getRotation().y == 270 ||
	rotate((getRotation().y < 270 && getRotation().y >= 90), elsapsedTime, 270))
      {
	savepos = glm::vec2(getfX(), getfY());
	move(270, elsapsedTime);
	newpos = glm::vec2(getfX(), getfY());
	if (savepos.x < pos.x && newpos.x >= pos.x)
	  {
	    setPosition(glm::vec3(pos.x, 0, pos.y));
	    return (bra = true);
	  }
	if (sqrt(pow(pos.x - savepos.x,2) + pow(pos.y - savepos.y, 2)) <= sqrt(pow(pos.x - newpos.x,2) + pow(pos.y - newpos.y, 2)))
	  {
	    setPosition(glm::vec3(savepos[0], 0, savepos[1]));
	    return (bra = true);
	  }
      }
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
      .addProperty("x", &PlayerAI::getX)
      .addProperty("y", &PlayerAI::getY)
      .addFunction("putBomb", &PlayerAI::putBomb)
      .endClass()
      .deriveClass<PlayerAI, Player>("PlayerAI")
      .addProperty("aiName", &PlayerAI::getAIName)
      .addProperty("goalX", &PlayerAI::getGoalX)
      .addProperty("goalY", &PlayerAI::getGoalY)
      .addFunction("moveRight", &PlayerAI::moveRight)
      .addFunction("moveLeft", &PlayerAI::moveLeft)
      .addFunction("moveUp", &PlayerAI::moveUp)
      .addFunction("moveDown", &PlayerAI::moveDown)
      .addFunction("memoriseGoal", &PlayerAI::memoriseGoal)
      .addFunction("resetGoal", &PlayerAI::resetGoal)
      .addFunction("isAttack", &PlayerAI::isAttack)
      .addFunction("isDefense", &PlayerAI::isDefense)
      .addFunction("memoriseAttack", &PlayerAI::memoriseAttackMode)
      .addFunction("memoriseDefense", &PlayerAI::memoriseDefenseMode)
      .endClass()
      .beginClass<GenericMap<AI::Cell> >("GenericMap")
      // .addProperty("width", &GenericMap<AI::Cell>::getWidth)
      // .addProperty("height", &GenericMap<AI::Cell>::getHeight)
      .endClass()
      .deriveClass<AI::StateMap, GenericMap<AI::Cell> >("StateMap")
      .addProperty("width", &AI::StateMap::getIntWidth)
      .addProperty("height", &AI::StateMap::getIntHeight)
      .addFunction("toString", &AI::StateMap::toString)
      .addFunction("getPlayerPosX", &AI::StateMap::getPlayerPosX)
      .addFunction("getPlayerPosY", &AI::StateMap::getPlayerPosY)
      .addFunction("getNbPlayers", &AI::StateMap::getNbPlayers)
      .addFunction("getCell", &AI::StateMap::getIntCell)
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

  /*
  ** Static protected methods
  */
  PlayerAI::MoveBook	PlayerAI::getMoveBook()
  {
    MoveBook		res;

    res[LEFT] = &PlayerAI::moveLeftCell;
    res[UP] = &PlayerAI::moveUpCell;
    res[DOWN] = &PlayerAI::moveDownCell;
    res[RIGHT] = &PlayerAI::moveRightCell;
    return (res);
  }
}
