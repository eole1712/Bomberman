#include "SdlContext.hh"
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
protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;

public:
  Object();
  virtual ~Object();

  glm::vec3	getPosition();
  glm::vec3	getRotation();
  glm::vec3	getScale();
  glm::mat4	getTransformation();
};

#endif /* !OBJECT_HPP_ */
