#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string.h>
#include "BasicShader.hh"
#include "Model.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifndef OBJECT_HPP_
# define OBJECT_HPP_

class Object
{
private:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  gdl::Model	_asset;
  bool		_visibility;

public:
  Object(std::string const &filename);
  ~Object();

  void update(gdl::Clock const &clock, gdl::Input &input);
  void draw(gdl::BasicShader &shader, gdl::Clock const &clock);
  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
  glm::mat4 getTransformation();
};

#endif /* !OBJECT_HPP_ */
