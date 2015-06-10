#ifndef AMENUOBJECT_H_
# define AMENUOBJECT_H_

#include "Geometry.hh"
#include "Texture.hh"
#include "BasicShader.hh"

class AMenuObject
{
public:
  AMenuObject(int x, int y, int width, int height, std::string const& textureName);
  virtual ~AMenuObject();
  void setHidden(bool hidden);
  bool isHidden();
  virtual void draw(gdl::BasicShader shader) = 0;
  int getX();
  int getY();

private:
  AMenuObject(const AMenuObject &);
  AMenuObject &operator=(const AMenuObject &);
protected:
  int	_x;
  int	_y;
  int	_width;
  int	_height;

  gdl::Texture	_texture;

  bool	_hidden;

};

#endif /* !AMENUOBJECT_H_ */
