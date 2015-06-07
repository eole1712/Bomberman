
#ifndef ASSET3D_H_
# define ASSET3D_H_

# include "Model.hh"
# include "Clock.hh"
# include "BasicShader.hh"
# include "Input.hh"
# include "Object3d.hpp"
# include "Timer.hpp"
# include "Animation.hpp"

class Asset3d : public Object3d, public gdl::Model
{
public:
Asset3d(std::string const &filename);
virtual ~Asset3d();

  unsigned int getAnimationFrame();
  unsigned int getAnimationSpeed();

  void  draw(gdl::BasicShader &shader, gdl::Clock const &clock);
  void	draw(gdl::BasicShader & shader, gdl::Clock const & clock,
	     Animation & animation);

private:
  bool		_visibility;
};

#endif /* !ASSET3D_H_ */
