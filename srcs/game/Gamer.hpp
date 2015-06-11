
#ifndef GAME_H_
# define GAME_H_

# include <vector>
# include <map>
# include "SdlContext.hh"
# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
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
# include "Text2d.hpp"
# include "IScene.hpp"

//# include "Core.hpp"

namespace Bomberman
{

class Gamer : public IScene
{
public:
  Gamer();
  Gamer(unsigned int, unsigned int, unsigned int, unsigned int);
  virtual ~Gamer();

  virtual bool		update(gdl::Clock &, gdl::Input &);
  virtual void		draw(gdl::Clock &, gdl::BasicShader &, CameraObject&, std::vector<Asset3d*>&,
			     std::map<Bomberman::IObject::Type, mapAsset>&);
  virtual void		drawAll(gdl::Clock &, gdl::BasicShader &, std::vector<Asset3d*>&,
				 std::map<Bomberman::IObject::Type, mapAsset>&);
  virtual void		drawPlayerArme(gdl::Clock &clock, gdl::BasicShader &shader,
				       std::vector<Asset3d*>& assets, Player *player,
				       std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset);
 //void			startGame();

private:
  Gamer(const Gamer &);
  Gamer &operator=(const Gamer &);

public:
  CameraObject			&getCamera(unsigned int);

private:
  int				_width;
  int				_height;
  JSONDoc			_json;

private:
  CameraObject			_camera;
  CameraObject			_camera2;

public:
  Bomberman::MapList*		_mapList;
  Bomberman::ScoreList*		_scoreList;
  Bomberman::RessourceStock*	_stock;
  Bomberman::Map*		_map;
};

}
#endif /* !GAME_H_ */
