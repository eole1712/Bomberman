
#ifndef GAME_H_
# define GAME_H_

# include <tuple>
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
# include "MenuGrid.hpp"
# include "ThreadPool.hpp"
# include "PlayerAI.hpp"

class JSONDoc;

namespace Bomberman
{

class Gamer : public IScene
{
public:
  Gamer(Map*, ScoreList*);
  Gamer(unsigned int, unsigned int, unsigned int, unsigned int,
	bool, std::string const&, std::string const&, unsigned int,
	Map*, ScoreList*);
  virtual ~Gamer();

public:
  virtual void		init(ScoreList*);
  virtual bool		update(gdl::Clock &, gdl::Input &);
  Bomberman::Map*	getMap() const;
  Bomberman::ScoreList*	getScoreList() const;
  Bomberman::RessourceStock* getRessourceStock() const;
  virtual void		draw(gdl::Clock &, gdl::BasicShader &, CameraObject&, std::vector<Asset3d*>&,
			     std::map<Bomberman::IObject::Type, mapAsset>&, Player *player);
  virtual void		drawAll(gdl::Clock &, gdl::BasicShader &, std::vector<Asset3d*>&,
				 std::map<Bomberman::IObject::Type, mapAsset>&);
  virtual void		drawPlayerArme(gdl::Clock &clock, gdl::BasicShader &shader,
				       std::vector<Asset3d*>& assets, Player *player,
				       std::map<Bomberman::IObject::Type, mapAsset> &ObjectToAsset);
  bool			pauseMenu();
  void			updateRandCamera();
  Player*		randAlivePlayer() const;
  void			drawEndGame(gdl::BasicShader &shader, Player *player);
  void			drawEndWin(gdl::BasicShader &shader, Player *player);

private:
  Gamer(const Gamer &);
  Gamer				&operator=(const Gamer &);

public:
  CameraObject			&getCamera(unsigned int);
  bool				is2Players();

public:
  void				setRcs(RessourceStock*);
  void				setMap(Map*);
  void				setWidth(unsigned int);
  void				setHeight(unsigned int);

protected:
  void				updateCamera();
  void				updateAllAI(const float elapsedTime);

protected:
  bool				handleKeyEvents(const float elapsedTime, gdl::Input& input,
						bool end = false);
  bool				handleKeyToPause(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP1PutBomb(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP2PutBomb(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP1Up(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP1Down(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP1Left(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP1Right(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP2Up(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP2Down(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP2Left(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToP2Right(const float elapsedTime, gdl::Input& input);
  bool				handleKeyToQuit(const float elapsedTime, gdl::Input& input);

public:
  RessourceStock*		getRcs() const;

private:
  int				_width;
  int				_height;
  MenuGrid*			_menu;
  bool				_quit;
  bool				_resume;
  bool				_twoPlayers;
  bool				_intro;
  bool				_viewMode;
  std::string			_player1;
  std::string			_player2;
  AI::StateMap			_stateMap;
  unsigned int			_nbPlayers;
  Player*			_spect;

private:
  CameraObject			_camera;
  CameraObject			_camera2;

public:
  Bomberman::RessourceStock*	_stock;
  Bomberman::Map*		_map;
  Bomberman::ScoreList*		_scoreList;

protected:
  typedef bool	(Gamer::*HandleKey)(const float elapsedTime, gdl::Input& input);
  typedef std::map<int, HandleKey>	HandleKeyBook;

  static const HandleKeyBook	handleKeyBook;
  static const HandleKeyBook	handleKeyBookIntro;
  static Gamer::HandleKeyBook	getHandleKeyBook();
  static Gamer::HandleKeyBook	getHandleKeyBookIntro();
};

}
#endif /* !GAME_H_ */
