#include "../include/celerytest.hpp"
#include "../include/celerytest_con.hpp"
#include "../include/celerytest_draw.hpp"

int main(int argc, char **argv) {
  celerytest::con::initialize();
  celerytest::con::listeners()->emplace_back(
      std::make_unique<celerytest::con::terminal_listener>());
  celerytest::con::log(celerytest::con::severity_t::echo, "Celerytest ",
                       celerytest_VSTRING_FULL, "\n");
  auto exit_status = EXIT_FAILURE;
  try {
    auto gui = std::make_unique<celerytest::draw::gui>(1920, 1080, false);

    gui->enable_3d();
    auto &&data_3d = gui->get_3d_data();
    data_3d->camera.position = Vector3{.x = 10.0f, .y = 10.0f, .z = 10.0f};
    data_3d->camera.target = Vector3{.x = 0.0f, .y = 0.0f, .z = 0.0f};
    data_3d->camera.up = Vector3{.x = 0.0f, .y = 1.0f, .z = 0.0f};
    data_3d->camera.fovy = 60.0f;
    data_3d->camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
      if (IsKeyPressed('Z')) {
        data_3d->camera.position = Vector3{.x = 10.0f, .y = 10.0f, .z = 10.0f};
        data_3d->camera.target = Vector3{.x = 0.0f, .y = 0.0f, .z = 0.0f};
        data_3d->camera.up = Vector3{.x = 0.0f, .y = 1.0f, .z = 0.0f};
      }
      celerytest::draw::tick(*gui);
    }

    // GUIs get freed automatically
    gui = nullptr;

    exit_status = EXIT_SUCCESS;
  } catch (const std::exception &e) {
    celerytest::con::log(celerytest::con::severity_t::error,
                         "ERROR: ", e.what(), "\n");
  }

  celerytest::con::cleanup();
  return exit_status;
}