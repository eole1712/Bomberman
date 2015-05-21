
#ifndef MYGAME_H_
# define MYGAME_H_

# include <list>
# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
# include "SdlContext.hh"
# include "BasicShader.hh"
# include "OpenGL.hh"
# include "Asset3d.hpp"
# include "CameraObject.hpp"

class MyGame : public gdl::Game
{
public:
  MyGame();
  virtual ~MyGame();

  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  void			attachObject(Asset3d *);
  void			translate(glm::vec3 const &v);

private:
  MyGame(const MyGame &);
  MyGame &operator=(const MyGame &);

  std::list<Asset3d *>	_objects;
  CameraObject		_camera;
  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  float			_speed;

protected:

};

#endif /* !MYGAME_H_ */
