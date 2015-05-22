
#include <string>
#include "Model.hh"
#include "Clock.hh"
#include "glm/glm.hpp"
#include "Asset3d.hpp"

Asset3d::Asset3d(std::string const &filename)
  :Object3d()
{
  _visibility = _asset.load(filename.c_str());
  _asset.setCurrentAnim(0);
}

Asset3d::~Asset3d(){}

void	Asset3d::update(gdl::Clock const &, gdl::Input &)
{

}

void	Asset3d::draw(gdl::BasicShader &shader, gdl::Clock const &clock)
{
  if (_visibility)
    _asset.draw(shader, getTransformation(), clock.getElapsed());
}
