
#ifndef MYGAME_H_
# define MYGAME_H_

# include <vector>
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

  enum			mapAsset
    {FLOOR, WALL, IDST_BLOCK
     ,DST_BLOCK, FIRE, PLAYER, BOMB, SKYBOX};
  std::vector<Asset3d *>	_assets;
  CameraObject		_camera;
  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  float			_speed;

  Object3d		_player;
};

#endif /* !MYGAME_H_ */
