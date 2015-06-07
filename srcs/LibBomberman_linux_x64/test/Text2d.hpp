
#ifndef TEXT2D
# define TEXT2D

#include <vector>
#include "Geometry.hh"
#include "Texture.hh"
#include "BasicShader.hh"

class Text2d
{
public:
  Text2d(std::string text, int x, int y, int width, int height, std::string textureName);
  ~Text2d();

  void	setHidden(bool hidden);
  void	draw(gdl::BasicShader shader);
private:

  Text2d();

private:
  std::string	_text;

  int	_x;
  int	_y;
  int	_width;
  int	_height;

  std::vector<gdl::Geometry*>	_geo;
  gdl::Texture			_texture;


  bool	_hidden;
};

#endif /* !TEXT2D */
