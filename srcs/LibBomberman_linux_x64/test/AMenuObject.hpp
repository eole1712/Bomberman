#ifndef AMENUOBJECT_H_
# define AMENUOBJECT_H_

# include "Geometry.hh"
# include "Texture.hh"
# include "BasicShader.hh"
# include "Input.hh"

class AMenuObject
{
public:
  AMenuObject(int x, int y, int width, int height, std::string const& textureName);
  virtual ~AMenuObject();
  void			setHidden(bool hidden);
  bool			isHidden() const;
  virtual void		draw(gdl::BasicShader shader) = 0;
  virtual int		getX() const;
  virtual int		getY() const;
  virtual int		getHeight() const;
  virtual void		update(gdl::Input&) = 0;
  void			unFocus();
  void			hideFocus();
  bool			isFocusable() const;
  bool			showFocus() const;
  void			setDynamic();
  bool			isDynamic() const;
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
  bool	_focusable;
  bool	_fShowable;
  bool	_dynamic;

};

#endif /* !AMENUOBJECT_H_ */
