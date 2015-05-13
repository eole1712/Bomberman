#ifndef __LUASCRIPT_HPP__
# define __LUASCRIPT_HPP__

# include <string>
# include "lua.hpp"

class LuaScript
{
public:
  typedef int	(*functionC)(lua_State *L);

public:
  LuaScript();
  LuaScript(std::string const& filename);
  ~LuaScript();

private:
  LuaScript(LuaScript const& other);
  LuaScript&	operator=(LuaScript const& other);

public:
  void		loadFile(std::string const& filename);
  void		registerFunction(std::string const& name, functionC f);
  void		run();

private:
  void		init();
  void		reportError(std::string const& where);

protected:
  lua_State*	_state;
  std::string	_filename;
};

#endif /* !__LUASCRIPT_HPP__ */
