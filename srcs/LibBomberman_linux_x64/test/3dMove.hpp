#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string.h>
#include "BasicShader.hh"
#include "Model.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifndef 3DMOVE_HPP_
# define 3DMOVE_HPP_

class 3dObject
{
protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;

public:
  3dObject();
  virtual ~3dObject();

  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
  glm::mat4 getTransformation();
};

#endif /* !3DMOVE_HPP_ */
