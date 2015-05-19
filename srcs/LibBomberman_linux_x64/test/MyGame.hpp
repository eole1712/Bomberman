#include <string>
#include <list>
#include "Game.hh"
#include "Clock.hh"
#include "Input.hh"
#include "SdlContext.hh"
#include "Geometry.hh"
#include "Texture.hh"
#include "BasicShader.hh"
#include "Model.hh"
#include "OpenGL.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VisibleObject.hpp"
#include "CameraObject.hpp"

#ifndef MYGAME_H_
# define MYGAME_H_

class MyGame : public gdl::Game
{
public:
  MyGame();
  virtual ~MyGame();

  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  void			attachObject(VisibleObject *);
  void			translate(glm::vec3 const &v);

private:
  MyGame(const MyGame &);
  MyGame &operator=(const MyGame &);

  std::list<VisibleObject *>	_objects;
  CameraObject		_camera;
  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  float			_speed;

protected:

};

#endif /* !MYGAME_H_ */
