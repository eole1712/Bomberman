//
// StringConversion.hh for  in /home/tea_a/Work/cpp_nibbler/sources
//
// Made by Alexandre Tea
// Login   <tea_a@epitech.net>
//
// Started on  Thu Mar 26 21:35:03 2015 Alexandre Tea
// Last update Sat Apr  4 00:00:46 2015 Alexandre Tea
//

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
