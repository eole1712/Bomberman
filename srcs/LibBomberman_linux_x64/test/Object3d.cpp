
#include "Object3d.hpp"

Object3d::Object3d()
  :
  _position(0, 0, 0),
  _rotation(0, 0, 0),
  _scale(1, 1, 1)
{
  ;
}

Object3d::~Object3d()
{
  ;
}

void		Object3d::translate(glm::vec3 const &v)
{
  _position += v;
}

void		Object3d::rotate(glm::vec3 const& axis,
			       float angle)
{
  _rotation += axis * angle;
}

void		Object3d::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}

void		Object3d::setPosition(glm::vec3 const& pos)
{
  _position = pos;
}

void		Object3d::setRotation(glm::vec3 const& rot)
{
  _rotation = rot;
}

void		Object3d::setScale(glm::vec3 const& scale)
{
  _scale = scale;
}

glm::vec3	Object3d::getPosition() const
{
  return _position;
}

glm::vec3	Object3d::getRotation() const
{
  return _rotation;
}

glm::vec3	Object3d::getScale() const
{
  return _scale;
}

glm::mat4	Object3d::getTransformation() const
{
  glm::mat4	transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}
