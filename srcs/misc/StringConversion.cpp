#include "StringConversion.hpp"

namespace Conversion
{

template <>
std::string		stringToType(std::string const& str)
{
  return (str);
}

}
