#include "LuaError.hpp"

namespace Exception
{
  LuaError::LuaError(std::string const& err) throw():
    std::runtime_error(err)
  {
  }

  LuaError::~LuaError() throw()
  {
  }
}
