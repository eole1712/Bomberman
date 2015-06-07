
#ifndef VIEW2D
# define VIEW2D

#include "Geometry.hh"
#include "Texture.hh"
#include "BasicShader.hh"

class View2d
{
public:
  View2d(int x, int y, int width, int height, std::string textureName);
  ~View2d();

  void	setHidden(bool hidden);
  void	draw(gdl::BasicShader shader);
private:

  View2d();

private:
  int	_x;
  int	_y;
  int	_width;
  int	_height;

  gdl::Geometry	_geo;
  gdl::Texture	_texture;


  bool	_hidden;
};

#endif /* !VIEW2D */
