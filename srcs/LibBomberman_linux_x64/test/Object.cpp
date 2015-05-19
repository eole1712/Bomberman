
#include "Object.hpp"

Object::Object()
  :
  _position(0, 0, 0),
  _rotation(0, 0, 0),
  _scale(1, 1, 1)
{
  ;
}

Object::~Object()
{
  ;
}

glm::vec3	Object::getPosition()
{
  return _position;
}

glm::vec3	Object::getRotation()
{
  return _rotation;
}

glm::vec3	Object::getScale()
{
  return _scale;
}

glm::mat4	Object::getTransformation()
{
  // On cree une matrice identite
  glm::mat4	transform(1);

  // On applique ensuite les rotations selon les axes x, y et z
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

  // On effectue ensuite la translation
  transform = glm::translate(transform, _position);

  // Et pour finir, on fait la mise a l'echelle
  transform = glm::scale(transform, _scale);

  return (transform);
}
