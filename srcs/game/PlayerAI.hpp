#ifndef __PLAYERAI_HPP__
# define __PLAYERAI_HPP__

# include <map>
# include <string>
# include "LuaBridge.h"
# include "lua.hpp"
# include "Player.hpp"
# include "LuaScript.hpp"
# include "Map.hpp"

namespace Bomberman
{
  class PlayerAI : public Player, public LuaScript
  {
  public:
    enum MoveDir
      {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
      };

  public:
    PlayerAI(std::string const& name, std::string const& script, glm::vec4 color);
    virtual ~PlayerAI();

  private:
    PlayerAI();
    PlayerAI(PlayerAI const& other);
    PlayerAI&		operator=(PlayerAI const& other);

  public:
    void		doAction(AI::StateMap const* stateMap, float const elapsedTime);
    std::string const&	getAIName() const;
    virtual bool		isIA() const;

  public:
    void		moveRight();
    void		moveLeft();
    void		moveUp();
    void		moveDown();

  protected:
    bool		moveRightCell(float const& elapsedTime);
    bool		moveLeftCell(float const& elapsedTime);
    bool		moveUpCell(float const& elapsedTime);
    bool		moveDownCell(float const& elapsedTime);

  protected:
    void		luaObjectInit();
    void		loadAIData();

  protected:
    typedef bool	(PlayerAI::*moveFc)(float const& elapsedTime);
    typedef std::map<MoveDir, moveFc>	MoveBook;

    static MoveBook	getMoveBook();

  protected:
    std::string		_aiName;
    luabridge::LuaRef*	_aiAction;
    MoveDir		_moveDir;
    std::pair<int, int>	_goal;
    bool		_attack;

  protected:
    static const MoveBook	moveBook;
  public:
    static const std::string	scriptName;
  };
}

#endif /* !__PLAYERAI_HPP__ */
