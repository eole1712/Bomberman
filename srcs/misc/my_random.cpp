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
  if (read(fd, &result, 4) == -1)
    return (min);
  return (result % (max - min) + min);
}

}
