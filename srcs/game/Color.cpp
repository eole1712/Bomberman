#include <math.h>
#include "Color.hpp"
#include "glm/glm.hpp"

#include <stdio.h>

namespace Bomberman
{

glm::vec4		Color::HSVtoRGB(double h, double s, double v)
{
  int		i;
  double	f;
  double	vpqt[4];
  const	int	vpqtToRgb[6][3] = {{0, 3, 1}, {2, 0, 1}, {1, 0, 3},
				   {1, 2, 0}, {3, 1, 0}, {0, 1, 2}};

  i = floor(h *  6);
  f = h * 6 - i;
  vpqt[0] = v;
  vpqt[1] = v * (1 - s);
  vpqt[2] = v * (1 - s * f);
  vpqt[3] = v * (1 - s * (1 - f));
  return glm::vec4(vpqt[vpqtToRgb[i][0]], vpqt[vpqtToRgb[i][1]],
		   vpqt[vpqtToRgb[i][2]], 0);
}

}
