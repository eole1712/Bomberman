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
#include "Object.hpp"

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
  void			attachObject(Object *);
  void			translate(glm::vec3 const &v);

private:
  MyGame(const MyGame &);
  MyGame &operator=(const MyGame &);

  std::list<Object *>	_objects;
  float			_fov;
  float			_height;
  float			_width;
  glm::vec3		_position;
  glm::vec3		_rotation;
  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  float			_speed;
  glm::mat4		_projection;
  glm::mat4		_transformation;

protected:

};

#endif /* !MYGAME_H_ */
