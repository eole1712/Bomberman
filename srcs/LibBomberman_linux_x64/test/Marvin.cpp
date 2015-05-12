//
// marvin.cpp for  in /home/gamain_j/rendu/cpp_bomberman
//
// Made by gamain_j gamain_j
// Login   <gamain_j@epitech.net>
//
// Started on  Tue May 12 18:13:03 2015 gamain_j gamain_j
// Last update Tue May 12 18:51:19 2015 gamain_j gamain_j
//

#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "BasicShader.hh"
#include "Model.hh"
#include "Clock.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Marvin.hpp"


Marvin::Marvin() :
  _position(0, 0, 0),
  _rotation(0, 0, 0),
  _scale(1, 1, 1)
{
}

Marvin::~Marvin(){}

bool Marvin::initialize()
{
  return (_asset.load("../assets/marvin.fbx"));
}

void Marvin::update(gdl::Clock const &, gdl::Input &)
{

}

void Marvin::draw(gdl::BasicShader &shader, gdl::Clock const &clock)
{
  _asset.draw(shader, getTransformation(), clock.getElapsed());
}

void Marvin::translate(glm::vec3 const &v)
{
  _position += v;
}

void Marvin::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
}

void Marvin::scale(glm::vec3 const& scale)
{
    _scale *= scale;
}

glm::mat4 Marvin::getTransformation()
{
  glm::mat4 transform(1); // On cree une matrice identite
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
