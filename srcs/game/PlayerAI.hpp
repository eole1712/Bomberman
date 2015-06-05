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
    PlayerAI(std::string const& name, std::string const& script);
    PlayerAI(std::string const& name, std::string const& script, glm::vec4 color);
    virtual ~PlayerAI();

  private:
    PlayerAI();
    PlayerAI(PlayerAI const& other);
    PlayerAI&		operator=(PlayerAI const& other);

  public:
    void		doAction(Map const& map, float const& elapsedTime);
    std::string const&	getAIName() const;

  public:
    void		moveRight();
    void		moveLeft();
    void		moveUp();
    void		moveDown();

  protected:
    void		moveRightFrame(float const& elapsedTime);
    void		moveLeftFrame(float const& elapsedTime);
    void		moveUpFrame(float const& elapsedTime);
    void		moveDownFrame(float const& elapsedTime);

  protected:
    void		luaObjectInit();
    void		loadAIData();

  protected:
    typedef void	(PlayerAI::*moveFc)(float const& elapsedTime);
    typedef std::map<MoveDir, moveFc>	MoveBook;

    static MoveBook	getMoveBook();

  protected:
    std::string		_aiName;
    luabridge::LuaRef*	_aiAction;
    MoveDir		_moveDir;

  protected:
    static const MoveBook	moveBook;
  };
}

#endif /* !__PLAYERAI_HPP__ */
