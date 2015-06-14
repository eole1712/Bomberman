#ifndef MENUGRID_H_
# define MENUGRID_H_

# include <vector>
# include <functional>
# include "AMenuObject.hpp"
# include "IScene.hpp"
# include "CameraObject.hpp"

class MenuGrid : public Bomberman::IScene
{
public:
  MenuGrid(std::string const& textName = "");
  virtual ~MenuGrid();
  void	moveLeft();
  void	moveRight();
  virtual void	drawAll(gdl::Clock &, gdl::BasicShader &, std::vector<Asset3d*>&,
			 std::map<Bomberman::IObject::Type, Bomberman::mapAsset>&);
  void		drawNoBack(gdl::BasicShader &);
  void	drawFocus(int x, int y, int height, gdl::BasicShader&);
  void	addObject(AMenuObject*, std::function<void()>);
  void	addDynObject(AMenuObject*, std::function<void()>, std::function<void()>, std::function<void()>);
  void	actionOnFocus();
  virtual bool		update(gdl::Clock &, gdl::Input &);
  //void			init();
private:
  MenuGrid(const MenuGrid &);
  MenuGrid &operator=(const MenuGrid &);
protected:
  std::vector<std::pair<AMenuObject*, std::function<void()> > >				_elems;
  std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator		_focus;
  std::vector<std::pair<std::function<void()>, std::function<void()> > >		_funcs;
  std::vector<std::pair<std::function<void()>, std::function<void()> > >::iterator	_fnFocus;
  std::function<void(int x, int y)>							_drawFocus;
  gdl::Texture										_focusTexture;
  CameraObject										_camera;
  int											_prev;
  std::function<void(void)>								_ftab[6];

};

#endif /* !MENUGRID_H_ */
