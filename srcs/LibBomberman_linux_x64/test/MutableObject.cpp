
#include "MutableObject.hpp"

MutableObject::MutableObject()
  :Object()
{

}

MutableObject::~MutableObject()
{

}


void		        MutableObject::translate(glm::vec3 const &v)
{
  _position += v;
}

void		        MutableObject::rotate(glm::vec3 const& axis,
						     float angle)
{
  _rotation += axis * angle;
}

void		        MutableObject::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}
