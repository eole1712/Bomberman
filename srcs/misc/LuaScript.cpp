#include <cstdlib>
#include "ResourceUnavailable.hpp"
#include "LuaError.hpp"
#include "LuaScript.hpp"

/*
** Constructors/Destructor
*/
LuaScript::LuaScript()
{
  init();
}

LuaScript::LuaScript(std::string const& filename)
{
  init();
  loadFile(filename);
}

LuaScript::~LuaScript()
{
  lua_close(_state);
}

/*
** Public member functions
*/
void	LuaScript::loadFile(std::string const& filename)
{
  if (filename.empty())
    throw Exception::LuaError("File loading failed: filename is empty");
  if (luaL_loadfile(_state, filename.c_str()) != LUA_OK)
    reportError("File loading");
  _filename = filename;
}

void	LuaScript::registerFunction(std::string const& name, functionC f)
{
  lua_register(_state, name.c_str(), f);
}

void	LuaScript::run()
{
  int	ret;

  if (_filename.empty())
    throw Exception::LuaError("Running script: no file loaded");
  if ((ret = lua_pcall(_state, 0, LUA_MULTRET, 0)) == LUA_ERRMEM)
    throw Exception::ResourceUnavailable("Running script: memory allocation failed");
  else if (ret != LUA_OK)
    reportError("Running script");
}

/*
** Private member functions
*/
void	LuaScript::init()
{
  if ((_state = luaL_newstate()) == NULL)
    throw Exception::ResourceUnavailable("Creating new state failed: memory allocation failed");
  luaL_openlibs(_state);
}

void	LuaScript::reportError(std::string const& where)
{
  char const*	err;

  if ((err = lua_tostring(_state, -1)) == NULL)
    return ;
  lua_pop(_state, 1);
  throw Exception::LuaError(where + " failed: " + std::string(err));
}
