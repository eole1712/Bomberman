
#ifndef MUTABLEOBJECT_HPP_
# define MUTABLEOBJECT_HPP_

#include "Object.hpp"

class MutableObject : public Object
{
public:
  MutableObject();
  virtual ~MutableObject();

  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
};

#endif /* !MUTABLEOBJECT_HPP_ */
