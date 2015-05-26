#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "my_random.hpp"

namespace Bomberman
{

unsigned int		my_random(int const min, int max)
{
  unsigned int	result;
  static int	fd = -1;

  if (min > max || (max - min) < 1
      || (fd == -1 && (fd = open("/dev/urandom", O_RDONLY)) == -1))
    return (min);
  max++;
  read(fd, &result, 4);
  return (result % (max - min) + min);
}

}
