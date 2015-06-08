
#ifndef TEXT2D
# define TEXT2D

#include <vector>
#include "AMenuObject.hpp"

class Text2d : public AMenuObject
{
public:
  Text2d(std::string const& text, int x, int y, int width, int height, std::string const& textureName);
  ~Text2d();

  void	setHidden(bool hidden);
  void	draw(gdl::BasicShader shader);
private:

  Text2d();

private:
  std::string	_text;
  std::vector<gdl::Geometry*>	_geo;
};

#endif /* !TEXT2D */
