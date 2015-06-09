#ifndef __PLAYERAI_HPP__
# define __PLAYERAI_HPP__

# include <string>
# include "LuaBridge.h"
# include "lua.hpp"
# include "Player.hpp"
# include "LuaScript.hpp"

namespace Bomberman
{
  class PlayerAI : public Player, public LuaScript
  {
  public:
    PlayerAI(std::string const& name, std::string const& script);
    virtual ~PlayerAI();

  private:
    PlayerAI();
    PlayerAI(PlayerAI const& other);
    PlayerAI&		operator=(PlayerAI const& other);

  public:
    void		doAction();
    std::string const&	getAIName() const;

public:
    bool		moveRight(float const & elsapsedTime,
				  unsigned int x, unsigned int y);
    bool		moveLeft(float const & elsapsedTime,
				 unsigned int x, unsigned int y);
    bool		moveUp(float const & elsapsedTime,
			       unsigned int x, unsigned int y);
    bool		moveDown(float const & elsapsedTime,
				 unsigned int x, unsigned int y);

  protected:
    void		luaObjectInit();
    void		loadAIData();

  protected:
    std::string		_aiName;
    luabridge::LuaRef*	_aiAction;
  };
}

#endif /* !__PLAYERAI_HPP__ */
