#include "InvalidDimensions.hpp"

namespace Exception
{
  InvalidDimensions::InvalidDimensions(std::string const& err) throw():
    std::runtime_error(err)
  {
  }

  InvalidDimensions::~InvalidDimensions() throw()
  {
  }
}
