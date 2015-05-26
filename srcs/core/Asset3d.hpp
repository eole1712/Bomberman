
#ifndef ASSET3D_H_
# define ASSET3D_H_

# include "Model.hh"
# include "BasicShader.hh"
# include "Input.hh"
# include "Object3d.hpp"

class Asset3d : public Object3d, public gdl::Model
{
public:
  Asset3d(std::string const &filename);
  virtual ~Asset3d();

  void	update(gdl::Clock const &, gdl::Input &);
  void  draw(gdl::BasicShader &shader, gdl::Clock const &clock);
  void	cutAnim();

private:
  bool		_visibility;
};

#endif /* !ASSET3D_H_ */
