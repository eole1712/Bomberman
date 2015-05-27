
#ifndef GAME_H_
# define GAME_H_

# include <vector>
# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
# include "SdlContext.hh"
# include "BasicShader.hh"
# include "OpenGL.hh"
# include "Asset3d.hpp"
# include "CameraObject.hpp"

# include "RessourceStock.hpp"
# include "Map.hpp"
# include "BuffFactory.hpp"
# include "BuffIncSpeed.hpp"
# include "BuffParalyzed.hpp"
# include "Player.hpp"

namespace Bomberman
{

class Game : public gdl::Game
{
public:
  Game();
  Game(const unsigned int & width, const unsigned int & height);
  virtual ~Game();

  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  void			attachObject(Asset3d *);
  void			translate(glm::vec3 const &v);

private:
  Game(const Game &);
  Game &operator=(const Game &);

  enum			mapAsset
    {FLOOR, WALL, IDST_BLOCK
     ,DST_BLOCK, FIRE, PLAYER, BOMB, SKYBOX};

  unsigned int			_width;
  unsigned int			_height;
  std::vector<Asset3d *>	_assets;
  CameraObject			_camera;
  gdl::SdlContext		_context;
  gdl::Clock			_clock;
  gdl::Input			_input;
  gdl::BasicShader		_shader;
  float				_speed;

  Bomberman::RessourceStock	_stock;
  Bomberman::Map		_map;
};

}
#endif /* !GAME_H_ */
