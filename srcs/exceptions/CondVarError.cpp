#include "CondVarError.hpp"

namespace Exception
{
  CondVarError::CondVarError(std::string const& err) throw():
    std::logic_error(err)
  {
  }

  CondVarError::~CondVarError() throw()
  {
  }
}
