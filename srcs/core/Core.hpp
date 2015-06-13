
#ifndef CORE_H_
# define CORE_H_

# include <vector>
# include <map>
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
# include "Game.hh"
# include "Gamer.hpp"

namespace Bomberman
{

class IScene;

class Core : public gdl::Game
{
public:
  Core();
  Core(const unsigned int & width, const unsigned int & height);
  virtual ~Core();

  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  void			attachObject(Asset3d *);
  void			loadTextures();
  void			startGame(bool twoPlayers = true, std::string const& p1 = "foo", std::string const& p2 = "bar");
  void			gameMenu();
  void			firstMenu();
  bool			isOver() const;
  void			intro();

private:
  Core(const Core &);
  Core &operator=(const Core &);

private:
  bool						_inGame;
  Bomberman::IScene*				_game;
  Bomberman::IScene*				_prev;
  bool						_change;


public:
  gdl::SdlContext		&getContext();
  gdl::Clock			&getClock();
  gdl::BasicShader		&getShader();

private:
  int				_width;
  int				_height;
  gdl::SdlContext		_context;
  gdl::Clock			_clock;
  gdl::Input			_input;
  gdl::BasicShader		_shader;
  float				_speed;
  bool				_status;

private:
  std::vector<Asset3d *>	_assets;
  std::map<Bomberman::IObject::Type, Bomberman::mapAsset>	_ObjectToAsset;
};

}
#endif /* !CORE_H_ */
