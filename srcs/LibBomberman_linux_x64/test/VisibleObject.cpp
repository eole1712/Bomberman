
#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "BasicShader.hh"
#include "Model.hh"
#include "Clock.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VisibleObject.hpp"

VisibleObject::VisibleObject(std::string const &filename)
  :MutableObject()
{
  _visibility = _asset.load(filename.c_str());
  _asset.setCurrentAnim(0);
}

VisibleObject::~VisibleObject(){}

void	VisibleObject::update(gdl::Clock const &, gdl::Input &)
{

}

void	VisibleObject::draw(gdl::BasicShader &shader, gdl::Clock const &clock)
{
  if (_visibility)
    _asset.draw(shader, getTransformation(), clock.getElapsed());
}
