
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
# include "ScoreList.hpp"
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
  virtual bool		update();
  virtual void		draw();
  void			attachObject(Asset3d *);
  void			translate(glm::vec3 const &v);
  virtual void		draw(gdl::Clock &, gdl::BasicShader &, CameraObject&);

private:
  Game(const Game &);
  Game &operator=(const Game &);

  enum			mapAsset
    {FLOOR, WALL, IDST_BLOCK
     ,DST_BLOCK, FIRE, PLAYER, BOMB, SKYBOX, BONUS};

public:
  gdl::SdlContext		&getContext();
  gdl::Clock			&getClock();
  gdl::BasicShader		&getShader();
  CameraObject			&getCamera(unsigned int);

private:
  int				_width;
  int				_height;
  std::vector<Asset3d *>	_assets;
  CameraObject			_camera;
  CameraObject			_camera2;
  gdl::SdlContext		_context;
  gdl::Clock			_clock;
  gdl::Input			_input;
  gdl::Input			_input2;
  gdl::BasicShader		_shader;
  float				_speed;
  std::map<Bomberman::IObject::Type, mapAsset>	_ObjectToAsset;
  JSONDoc			_json;
  Bomberman::MapList*		_mapList;
  Bomberman::ScoreList*		_scoreList;
  Bomberman::RessourceStock*	_stock;
  Bomberman::Map*		_map;
};

}
#endif /* !GAME_H_ */
