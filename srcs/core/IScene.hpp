#ifndef ISCENE_H_
# define ISCENE_H_

# include <vector>
# include <map>

# include "Asset3d.hpp"
# include "Input.hh"
# include "BasicShader.hh"
# include "IObject.hpp"
# include "Clock.hh"

namespace Bomberman
{
  enum                  mapAsset
    {
      FLOOR,
      WALL,
      IDST_BLOCK,
      DST_BLOCK,
      FIRE,
      PLAYER,
      BOMB,
      SKYBOX,
      BONUS,
      BARREL,
      MINE,
      VIRUS
    };
class IScene
{
public:
  IScene() {}
  virtual ~IScene() {}
  virtual void	drawAll(gdl::Clock &, gdl::BasicShader &, std::vector<Asset3d*>&,
			 std::map<Bomberman::IObject::Type, mapAsset>&) = 0;
  virtual bool	update(gdl::Clock &, gdl::Input&) = 0;
};

}
#endif /* !ISCENE_H_ */
