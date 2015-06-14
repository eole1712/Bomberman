#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef OBJECT3D_HPP_
# define OBJECT3D_HPP_

class Object3d
{
protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;

public:
  Object3d();
  virtual ~Object3d();

  glm::vec3 const&	getPosition() const;
  glm::vec3 const&	getRotation() const;
  glm::vec3 const&	getScale() const;
  void			setPosition(glm::vec3 const& pos);
  void			setRotation(glm::vec3 const& rot);
  void			setScale(glm::vec3 const& scale);
  glm::mat4		getTransformation() const;
  void			translate(glm::vec3 const &v);
  void			rotate(glm::vec3 const& axis, float angle);
  void			scale(glm::vec3 const& scale);
};

#endif /* !OBJECT3D_HPP_ */
