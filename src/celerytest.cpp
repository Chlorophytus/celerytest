#include "celerytest.hpp"
#include "celerytest_con.hpp"

int main(int argc, char **argv) {
  celerytest::con::initialize();
  celerytest::con::listeners()->emplace_back(
      std::make_unique<celerytest::con::terminal_listener>());
  celerytest::con::log(celerytest::con::severity_t::echo, "Celerytest ",
                       celerytest_VSTRING_FULL, "\n");
  celerytest::con::log(celerytest::con::severity_t::echo, "hello\n");
  celerytest::con::cleanup();
  return EXIT_SUCCESS;
}