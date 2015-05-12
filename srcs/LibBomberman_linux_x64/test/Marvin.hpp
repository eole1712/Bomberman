#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "BasicShader.hh"
#include "Model.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifndef MARVIN_HPP_
# define MARVIN_HPP_

class Marvin
{
private:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  gdl::Model	_asset;

public:
  Marvin();
  ~Marvin();

  bool initialize();
  void update(gdl::Clock const &clock, gdl::Input &input);
  void draw(gdl::BasicShader &shader, gdl::Clock const &clock);
  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
  glm::mat4 getTransformation();
};

#endif /* !MARVIN_HPP_ */
