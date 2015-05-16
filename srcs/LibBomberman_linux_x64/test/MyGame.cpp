#include <list>
#include <string>
#include <algorithm>
#include "MyGame.hpp"
#include "Object.hpp"

MyGame::MyGame()
  : _fov(90.0), _height(1000), _width(1000),
    _position(0.0, 4.0, 4.0),
    _rotation(0.0, 0.0, 0.0),
    _speed(70)
{
}

MyGame::~MyGame()
{
  for (std::list<Object *>::iterator i = _objects.begin(); i != _objects.end(); i++)
    delete (*i);
}

bool		MyGame::initialize()
{
  if (!_context.start(_height, _width, "My bomberman!"))
    return false;
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  // We create a shader
  if (!_shader.load("../shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("../shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;

  // We set the camera
  _projection = glm::perspective(_fov, _height / _width, 0.1f, 1000.0f);
  _transformation = glm::lookAt(_position, _rotation, glm::vec3(0, 1, 0));
  // We have the bind the shader before calling the setUniform method
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  return true;
}

void		MyGame::attachObject(Object *obj)
{
  _objects.push_front(obj);
}

bool		MyGame::update()
{
  float		movefactor;

  movefactor = static_cast<float>(_clock.getElapsed()) * _speed;
  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_input.getKey(SDLK_UP))
    translate(glm::vec3(0, 0, -1) * movefactor);
  if (_input.getKey(SDLK_DOWN))
    translate(glm::vec3(0, 0, 1) * movefactor);
  if (_input.getKey(SDLK_LEFT))
    translate(glm::vec3(-1, 0, 0) * movefactor);
  if (_input.getKey(SDLK_RIGHT))
    translate(glm::vec3(1, 0, 0) * movefactor);
  _transformation = glm::lookAt(_position, _rotation, glm::vec3(0, 1, 0));
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);

  return true;
}

void		MyGame::translate(glm::vec3 const &v)
{
  _position += v;
}

void		MyGame::draw()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  // We draw all objects
  for (std::list<Object *>::iterator i = _objects.begin(); i != _objects.end(); i++)
    (*i)->draw(_shader, _clock);
  _context.flush();
}
