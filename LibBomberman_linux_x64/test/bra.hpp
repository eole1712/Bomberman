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

#ifndef BRADQZEIOFJ_H_
# define BRADQZEIOFJ_H_

class MyGame : public gdl::Game
{
public:
  MyGame();
  virtual ~MyGame();

  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();

private:
  MyGame(const MyGame &);
  MyGame &operator=(const MyGame &);

  gdl::SdlContext _context;
  gdl::Clock _clock;
  gdl::Input _input;
  gdl::BasicShader _shader;
  // std::vector<AObject*> _objects;
protected:

};

#endif /* !BRA_H_ */
