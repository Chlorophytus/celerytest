#include "celerytest.hpp"
#include "celerytest_con.hpp"
#include "celerytest_gl.hpp"

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  celerytest::con::initialize();
  celerytest::con::listeners()->emplace_back(
      std::make_unique<celerytest::con::terminal_listener>());
  celerytest::con::log(celerytest::con::severity_t::echo, "Celerytest ",
                       celerytest_VSTRING_FULL, "\n");

  celerytest::gl::window_initialize(1024, 600, false);
  
  for (auto i = 0; i < 512; i++) {
    celerytest::gl::tick();
    SDL_Delay(10);
  }
  
  celerytest::gl::window_cleanup();
  celerytest::con::cleanup();
  SDL_Quit();
  return EXIT_SUCCESS;
}