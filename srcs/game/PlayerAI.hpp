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
    PlayerAI();
    ~PlayerAI();

  public:
    PlayerAI(std::string const& script);

  private:
    PlayerAI(PlayerAI const& other);
    PlayerAI&		operator=(PlayerAI const& other);

  protected:
  };
}

#endif /* !__PLAYERAI_HPP__ */
