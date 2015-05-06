#ifndef __STRINGCONVERSION_HPP__
# define __STRINGCONVERSION_HPP__

# include <iostream>
# include <iomanip>
# include <sstream>

namespace Conversion
{

template <typename T>
T			stringToType(std::string const& str)
{
  T			res;
  std::istringstream	ss(str);

  ss >> res;
  return (res);
}

template <typename T>
std::string		typeToString(T const& type)
{
  std::ostringstream	ss;

  ss << std::fixed << type;
  return (ss.str());
}

}

#endif /* !__STRINGCONVERSION_HPP__ */
