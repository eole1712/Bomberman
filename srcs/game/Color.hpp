
#include "glm/glm.hpp"

# ifndef COLOR_HPP_
# define COLOR_HPP_

namespace Bomberman
{
  class Color
  {
  public:
    static glm::vec4	HSVtoRGB(double h, double s, double v);
  };
}

# endif /* !COLOR_HPP_ */
