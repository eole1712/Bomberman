
#include <iostream>
#include <string>
#include "Model.hh"
#include "Clock.hh"
#include "glm/glm.hpp"
#include "Asset3d.hpp"

Asset3d::Asset3d(std::string const &filename)
  :Object3d(), gdl::Model()
{
  _visibility = load(filename.c_str());
  setCurrentAnim(1);
}

Asset3d::~Asset3d(){}

void	Asset3d::draw(gdl::BasicShader &shader, gdl::Clock const &clock)
{
  if (_visibility)
    gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
}
