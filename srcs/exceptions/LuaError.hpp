#ifndef __LUAERROR_HPP__
# define __LUAERROR_HPP__

# include <string>
# include <stdexcept>

namespace Exception
{
  class LuaError : public std::runtime_error
  {
  public:
    LuaError(std::string const& err) throw();
    virtual ~LuaError() throw();
  };
}

#endif /* !__LUAERROR_HPP__ */
