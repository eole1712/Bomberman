#include "InvalidNbPlayers.hpp"

namespace Exception
{
  InvalidNbPlayers::InvalidNbPlayers(std::string const& err) throw():
    std::runtime_error(err)
  {
  }

  InvalidNbPlayers::~InvalidNbPlayers() throw()
  {
  }
}
