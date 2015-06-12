#include <iostream>
#include <fstream>
#include "my_random.hpp"

namespace Bomberman
{

unsigned int		my_random(int const min, int max)
{
  unsigned int		result;
  static std::ifstream	frand("/dev/urandom");

  if (min > max || (max - min) < 1 || !frand)
    return (min);
  max++;
  frand.read(reinterpret_cast<char *>(&result), 4);
  return (result % (max - min) + min);
}

}
