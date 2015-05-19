
#ifndef VISIBLEOBJECT_H_
# define VISIBLEOBJECT_H_

# include "MutableObject.hpp"

class VisibleObject : public MutableObject
{
public:
  VisibleObject(std::string const &filename);
  virtual ~VisibleObject();

  void	update(gdl::Clock const &, gdl::Input &);
  void  draw(gdl::BasicShader &shader, gdl::Clock const &clock);

private:
  gdl::Model	_asset;
  bool		_visibility;
};

#endif /* !VISIBLEOBJECT_H_ */
