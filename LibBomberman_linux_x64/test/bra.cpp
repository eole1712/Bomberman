
#include "bra.hpp"

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

bool		MyGame::initialize()
{
  if (!_context.start(800, 600, "My bomberman!")) // on cree une fenetre
    return false;
  // Activates the OpenGL depth test for the pixels that the eye does not see does not  appear
    glEnable(GL_DEPTH_TEST);
  // We create a shader
  if (!_shader.load("../shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("../shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;
  // We set the camera
  glm::mat4 projection;
  glm::mat4 transformation;
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  // We have the bind the shader before calling the setUniform method
  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
  // We create a cube that we had to the objects list
  // AObject *cube = new Cube();
  // if (cube->initialize() == false)
  //   return (false);
  // _objects.push_back(cube);
  return true;
}

bool		MyGame::update()
{
  // If the escape key is pressed or if the window has been closed we stop the program
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  // Update inputs an clock
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  // We update the objects
  // for (size_t i = 0; i < _objects.size(); ++i)
  //   _objects[i]->update(_clock, _input);
  return true;
}

void		MyGame::draw()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // We bind the shader to be able to draw the geometry
  // We can only have one shader at a time
  _shader.bind();
  // We draw the objects
  // for (size_t i = 0; i < _objects.size(); ++i)
  //   _objects[i]->draw(_shader, _clock);
  // We update the screen
  _context.flush();
}


int main()
{
  MyGame	engine;
  // create the engine

  if (engine.initialize() == false)
    return (EXIT_FAILURE);
  while (engine.update() == true)
    engine.draw();
  return EXIT_SUCCESS;
}
