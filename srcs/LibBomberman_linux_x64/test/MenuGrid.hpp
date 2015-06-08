#ifndef MENUGRID_H_
# define MENUGRID_H_

# include <vector>
# include <functional>
# include "AMenuObject.hpp"

class MenuGrid
{
public:
  MenuGrid(std::string const& textName = "");
  virtual ~MenuGrid();
  void	moveLeft();
  void	moveRight();
  void	drawGrid(gdl::BasicShader&);
  void	drawFocus(int x, int y, gdl::BasicShader&);
  void	addObject(AMenuObject*, std::function<void()>);
  void	actionOnFocus();
private:
  MenuGrid(const MenuGrid &);
  MenuGrid &operator=(const MenuGrid &);
protected:
  std::vector<std::pair<AMenuObject*, std::function<void()> > >			_elems;
  std::vector<std::pair<AMenuObject*, std::function<void()> > >::iterator	_focus;
  std::function<void(int x, int y)>						_drawFocus;
  gdl::Texture									_focusTexture;
};

#endif /* !MENUGRID_H_ */
