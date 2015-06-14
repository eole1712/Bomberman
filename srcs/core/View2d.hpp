
#ifndef VIEW2D
# define VIEW2D

#include "AMenuObject.hpp"

class View2d : public AMenuObject
{
public:
  View2d(int x, int y, int width, int height, std::string const& textureName);
  virtual ~View2d();

  void	draw(gdl::BasicShader shader);
  void	update(gdl::Input&);
private:
  View2d();
private:
  gdl::Geometry	_geo;

};

#endif /* !VIEW2D */
