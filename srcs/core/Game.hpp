
#ifndef GAME_H_
# define GAME_H_

# include <vector>
# include <map>
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
# include "Score.hpp"
# include "BuffFactory.hpp"
# include "BuffIncSpeed.hpp"
# include "BuffParalyzed.hpp"
# include "Player.hpp"
# include "JSONDoc.hpp"

namespace Bomberman
{

class Game : public gdl::Game
{
public:
  Game();
  Game(const unsigned int & width, const unsigned int & height);
  virtual ~Game();

  virtual bool		initialize();
  virtual bool		initialize2();
  virtual bool		update();
  virtual void		draw();
  void			attachObject(Asset3d *);
  void			translate(glm::vec3 const &v);
  virtual void		draw(gdl::SdlContext &, gdl::Clock &, gdl::BasicShader &, CameraObject&);
  void			change();

private:
  Game(const Game &);
  Game &operator=(const Game &);

  enum			mapAsset
    {FLOOR, WALL, IDST_BLOCK
     ,DST_BLOCK, FIRE, PLAYER, BOMB, SKYBOX, BONUS};

public:
  gdl::SdlContext		&getContext(unsigned int);
  gdl::Clock			&getClock(unsigned int);
  gdl::BasicShader		&getShader(unsigned int);
  CameraObject			&getCamera(unsigned int);

private:
  int				_width;
  int				_height;
  std::vector<Asset3d *>	_assets;
  CameraObject			_camera;
  CameraObject			_camera2;
  gdl::SdlContext		_context;
  gdl::SdlContext		_context2;
  gdl::Clock			_clock;
  gdl::Clock			_clock2;
  gdl::Input			_input;
  gdl::Input			_input2;
  gdl::BasicShader		_shader;
  gdl::BasicShader		_shader2;
  float				_speed;
  SDL_Window			*win;
  std::map<Bomberman::IObject::Type, mapAsset>	_ObjectToAsset;
  bool				_change;
  JSONDoc			_json;
  Bomberman::RessourceStock*	_stock;
  Bomberman::Map*		_map;
  Bomberman::ScoreList		_scores;
};

}
#endif /* !GAME_H_ */
