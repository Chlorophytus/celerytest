#include "celerytest_gl.hpp"
#include "celerytest_con.hpp"

using namespace celerytest;

static gl::window_t *window = nullptr;
static std::unique_ptr<gl::context_t> context = nullptr;

void gl::window_initialize(U16 width, U16 height, bool fullscreen) {
  if (window != nullptr) {
    con::log(con::severity_t::fatal, "A window already exists\n");
  }
  con::log(con::severity_t::echo, "Making a ", width, "x", height, " window\n");
  con::log(con::severity_t::echo, "Fullscreen = ", fullscreen, "\n");

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  if (fullscreen) {
    window = SDL_CreateWindow("Celerytest", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
  } else {
    window = SDL_CreateWindow("Celerytest", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
  }

  if (window == nullptr) {
    con::log(con::severity_t::fatal, "Can't create window: ", SDL_GetError(),
             "\n");
  }

  glewExperimental = GL_TRUE;
  context = std::make_unique<context_t>(SDL_GL_CreateContext(window));
  auto glew_result = glewInit();

  if (glew_result != GLEW_OK) {
    con::log(con::severity_t::error,
             "GLEW extension loader failed, but the engine may still be "
             "functional: ",
             glewGetErrorString(glew_result), "\n");
  }
}

void gl::tick() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
  SDL_GL_SwapWindow(window);
}

void gl::window_cleanup() {
  if (window == nullptr) {
    con::log(con::severity_t::fatal, "Can't destroy a nonexistant window\n");
  }
  if (context == nullptr) {
    con::log(con::severity_t::fatal,
             "Can't destroy a window without its OpenGL context\n");
  }
  con::log(con::severity_t::echo, "Destroying the window\n");
  SDL_GL_DeleteContext(*context);
  context = nullptr; // manual set to nullptr, SDL doesn't do it for us
  SDL_DestroyWindow(window);
}