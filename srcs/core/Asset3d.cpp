#include <exception>
#include <string>
#include <sstream>
#include "Model.hh"
#include "Clock.hh"
#include "glm/glm.hpp"
#include "Asset3d.hpp"
#include "Animation.hpp"

Asset3d::Asset3d(std::string const &filename)
  :Object3d(), gdl::Model(), _visibility(true)
{
  int			framecount;
  std::stringstream	ss;

  if (!load(filename.c_str()))
      throw (std::runtime_error(filename + ": Can't load asset: no such file"));
  framecount = 0;
  while (framecount < gdl::Model::getAnimationFrameNumber(0)
	 && (ss << framecount)
	 && gdl::Model::createSubAnim(0, ss.str(), framecount, framecount))
    {
      ss.str("");
      framecount++;
    }
}

Asset3d::~Asset3d(){}

unsigned int Asset3d::getAnimationFrame()
{
  return (gdl::Model::getAnimationFrameNumber(0));
}

unsigned int Asset3d::getAnimationSpeed()
{
  return (gdl::Model::getFrameDuration() * 1000000);
}

void		Asset3d::draw(gdl::BasicShader &shader, gdl::Clock const &clock)
{
  if (_visibility)
    gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
}

void		Asset3d::draw(gdl::BasicShader & shader, gdl::Clock const & clock,
			      Animation & animation)
{
  if (_visibility)
    {
      gdl::Model::setCurrentSubAnim(animation.getFrameName(), false);
      gdl::Model::draw(shader, getTransformation(), clock.getElapsed());
    }
}
